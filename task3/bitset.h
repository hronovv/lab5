#ifndef TASK3_BITSET_H
#define TASK3_BITSET_H

#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>


template<size_t amount_of_bits>
class GoodBitset {
    static constexpr size_t kBitsPerBlock = 64; // each block contains 64 bits
    static constexpr size_t kBlocksCount = (amount_of_bits + kBitsPerBlock - 1) / kBitsPerBlock; // ceil(a/b) = (a+b-1)/b;
    std::vector<uint64_t> blocks;

public:
    GoodBitset() : blocks(kBlocksCount, 0) {}
    GoodBitset(const GoodBitset &other_bitset) : blocks(other_bitset.blocks) {}
    explicit GoodBitset(uint64_t number) : blocks(kBlocksCount, 0) {
        blocks[0] = number;
    } // if length of the number in binary > bits in bitset -> UB, cause part of the number will be vanished

    /*
     *
     * BELOW IS PROXY CLASS( USING PROXY PATTERN)
     */
    class BitReference {
        uint64_t& block;
        size_t bit;

    public:
        BitReference(uint64_t& block, size_t bit) : block(block), bit(bit) {}

        operator bool() const {
            return (block >> bit) & 1ULL;
        }

        BitReference& operator=(bool val) {
            if (val)
                block |= (1ULL << bit);
            else
                block &= ~(1ULL << bit);
            return *this;
        }

        BitReference& operator=(const BitReference& other) {
            return *this = static_cast<bool>(other);
        }

        BitReference& flip() {
            block ^= (1ULL << bit);
            return *this;
        }
    };

    BitReference operator[](size_t pos) {
        if (pos >= amount_of_bits) throw std::out_of_range("Index out of range");
        return BitReference(blocks[pos / kBitsPerBlock], pos % kBitsPerBlock);
    }

    GoodBitset& operator=(const GoodBitset& other) {
        if (this != &other) {
            blocks = other.blocks;
        }
        return *this;
    }

    GoodBitset operator& (const GoodBitset &other) const {
        GoodBitset res;
        for (size_t i = 0; i < kBlocksCount; i++)
            res.blocks[i] = blocks[i] & other.blocks[i];
        return res;
    }

    GoodBitset operator| (const GoodBitset &other) const {
        GoodBitset res;
        for (size_t i = 0; i < kBlocksCount; i++)
            res.blocks[i] = blocks[i] | other.blocks[i];
        return res;
    }

    GoodBitset operator^ (const GoodBitset &other) const {
        GoodBitset res;
        for (size_t i = 0; i < kBlocksCount; i++)
            res.blocks[i] = blocks[i] ^ other.blocks[i];
        return res;
    }

    GoodBitset& operator&= (const GoodBitset &other) {
        for (size_t i = 0; i < kBlocksCount; i++)
            blocks[i] &= other.blocks[i];
        return *this;
    }

    GoodBitset& operator|= (const GoodBitset &other) {
        for (size_t i = 0; i < kBlocksCount; i++)
            blocks[i] |= other.blocks[i];
        return *this;
    }

    GoodBitset& operator^= (const GoodBitset &other) {
        for (size_t i = 0; i < kBlocksCount; i++)
            blocks[i] ^= other.blocks[i];
        return *this;
    }


    GoodBitset operator<<(size_t shift) const {
        GoodBitset result = *this;
        result <<= shift;
        return result;
    }

    GoodBitset operator>>(size_t shift) const {
        GoodBitset result = *this;
        result >>= shift;
        return result;
    }

    GoodBitset& operator<<=(size_t shift) {
        if (shift >= amount_of_bits) {
            reset();
            return *this;
        }
        size_t block_shift = shift / kBitsPerBlock;
        size_t bit_shift = shift % kBitsPerBlock;

        std::vector<uint64_t> new_blocks(kBlocksCount, 0);
        for (size_t i = block_shift; i < kBlocksCount; ++i) {
            new_blocks[i] = blocks[i - block_shift] << bit_shift;
            if (bit_shift != 0 && i > block_shift)
                new_blocks[i] |= blocks[i - block_shift - 1] >> (kBitsPerBlock - bit_shift);
        }
        blocks = std::move(new_blocks);
        size_t rem = amount_of_bits % kBitsPerBlock;
        if (rem != 0) {
            blocks.back() &= (1ULL << rem) - 1;
        }
        return *this;
    }

    GoodBitset& operator>>=(size_t shift) {
        if (shift >= amount_of_bits) {
            reset();
            return *this;
        }
        size_t block_shift = shift / kBitsPerBlock;
        size_t bit_shift = shift % kBitsPerBlock;
        std::vector<uint64_t> new_blocks(kBlocksCount, 0);
        for (size_t i = 0; i + block_shift < kBlocksCount; ++i) {
            new_blocks[i] = blocks[i + block_shift] >> bit_shift;
            if (bit_shift != 0 && i + block_shift + 1 < kBlocksCount)
                new_blocks[i] |= blocks[i + block_shift + 1] << (kBitsPerBlock - bit_shift);
        }

        blocks = std::move(new_blocks);
        return *this;
    }


    [[nodiscard]] bool all() const {
        for (size_t i = 0; i < kBlocksCount - 1; ++i)
            if (blocks[i] != UINT64_MAX) return false;

        size_t rem = amount_of_bits % kBitsPerBlock;
        uint64_t mask = (rem == 0) ? UINT64_MAX : (1ULL << rem) - 1;
        return (blocks.back() & mask) == mask;
    }

    [[nodiscard]] bool any() const {
        for (size_t i = 0; i < kBlocksCount - 1; ++i) {
            if (blocks[i] != 0) return true;
        }

        size_t rem = amount_of_bits % kBitsPerBlock;
        if (rem == 0)  {
            return blocks.back() != 0;
        }

        uint64_t mask = (1ULL << rem) - 1;
        return (blocks.back() & mask) != 0;
    }


    [[nodiscard]] bool none() const {
        return !any();
    }

    [[nodiscard]] size_t size() const {
        return amount_of_bits;
    }

    [[nodiscard]] bool test(size_t pos) const {
        if (pos >= amount_of_bits) {
            throw std::out_of_range("Bit position out of range");
        }

        size_t block_index = pos / kBitsPerBlock;  // index of the block
        size_t bit_index = pos % kBitsPerBlock;    // index of the bit in the block

        return (blocks[block_index] & (1ULL << bit_index)) != 0;
    }

    [[nodiscard]] bool operator[](size_t pos) const {
        return test(pos);
    }

    [[nodiscard]] size_t count() const {
        size_t bits = 0;
        for (size_t i = 0; i < kBlocksCount - 1; i++) {
            bits += __builtin_popcountll(blocks[i]);
        }
        size_t last_bits = amount_of_bits % kBitsPerBlock;
        if (last_bits == 0) {
            last_bits = kBitsPerBlock;
        }
        uint64_t mask = (1ULL << last_bits) - 1;
        bits += __builtin_popcountll(blocks.back() & mask);
        return bits;
    }

    void flip() {
        for (size_t i = 0; i < kBlocksCount; ++i) {
            blocks[i] = ~blocks[i];
        }
    }

    void flip(size_t pos) {
        if (pos >= amount_of_bits)
            throw std::out_of_range("Bit position out of range");

        size_t block_idx = pos / kBitsPerBlock;
        size_t bit_idx = pos % kBitsPerBlock;
        blocks[block_idx] ^= (1ULL << bit_idx);
    }

    void reset() {
        for (auto& block : blocks)
            block = 0;
    } // just setting all bits to 0

    void reset(size_t pos) {
        if (pos >= amount_of_bits)
            throw std::out_of_range("Bit position out of range");

        size_t block_idx = pos / kBitsPerBlock;
        size_t bit_idx = pos % kBitsPerBlock;
        blocks[block_idx] &= ~(1ULL << bit_idx);
    }

    void set() {
        for (size_t i = 0; i < kBlocksCount - 1; ++i)
            blocks[i] = ~0ULL; 

        size_t remaining_bits = amount_of_bits % kBitsPerBlock;
        if (remaining_bits == 0) {
            blocks[kBlocksCount - 1] = ~0ULL;
        } else {
            blocks[kBlocksCount - 1] = (1ULL << remaining_bits) - 1;
        }
    }

    void set(size_t pos) {
        if (pos >= amount_of_bits)
            throw std::out_of_range("Bit position out of range");

        size_t block_idx = pos / kBitsPerBlock;
        size_t bit_idx = pos % kBitsPerBlock;
        blocks[block_idx] |= (1ULL << bit_idx);
    }

    [[nodiscard]] std::string to_string() const {
        std::string res(amount_of_bits, '0');
        /*
         filling all symbols by '0' just to not change them in the future in the if-else block
        */
        for (size_t i = 0; i < amount_of_bits; i++) {
            if (test(i)) { // if bit is 1
                res[amount_of_bits - 1 - i] = '1';
            }
        }
        return res;
    }

    [[nodiscard]] unsigned long long to_ullong() const {
        // if constexpr (amount_of_bits >= 64) {
        //     return blocks[0];
        // } else {
        //     return blocks[0] & ((1ULL << amount_of_bits) - 1); //using mask
        // }
        return blocks[0]; // COMPARE LATER - TO-DO
    }

    [[nodiscard]] unsigned long to_ulong() const {
        if constexpr (amount_of_bits >= 32) {
            return static_cast<unsigned long>(blocks[0]);
        } else {
            return static_cast<unsigned long>(blocks[0] & ((1ULL << amount_of_bits) - 1));
        }
    }
};

template<size_t N>
std::ostream& operator<<(std::ostream& os, const GoodBitset<N>& bitset) {
    return os << bitset.to_string();
} // cout of GoodBitset

template<size_t N>
std::istream& operator>>(std::istream& is, GoodBitset<N>& bitset) {
    std::string input;
    is >> input;

    if (input.length() > N) {
        is.setstate(std::ios::failbit);
        return is;
    }

    bitset.reset();
    size_t offset = N - input.length();
    for (size_t i = 0; i < input.length(); ++i) {
        char c = input[i];
        if (c == '1') {
            bitset.set(N - 1 - (i + offset));
        } else if (c != '0') {
            is.setstate(std::ios::failbit);
            return is;
        }
    }
    return is;
}


#endif //TASK3_BITSET_H
