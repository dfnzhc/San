//
// Created by 秋鱼 on 2022/6/12.
//

#pragma once

#include <logger.hpp>
namespace San {

/**
 * @brief 一个简单的环形分配结构，它从尾部分配新的内存，从头部释放。
 */
class Ring
{
public:
    void create(uint32_t totalSize)
    {
        head_ = 0;
        allocated_size_ = 0;
        total_size_ = totalSize;
    }

    // 避免分配的内存跨越环形缓冲区的头尾
    uint32_t getPaddingToAvoidCrossOver(uint32_t size)
    {
        int tail = getTail();

        if (tail + size > total_size_) {
            return total_size_ - tail;
        }

        return 0;
    }

    /**
     * @brief 表示为分配内存
     * @param offset: 返回与起始位置间的位移
     */
    bool alloc(uint32_t size, uint32_t* offset = nullptr)
    {
        if (allocated_size_ + size <= total_size_) {
            if (offset) {
                *offset = getTail();
            }

            allocated_size_ += size;
            return true;
        }
        
        LOG_FATAL("Allocate failed.")
        return false;
    }
    
    /**
     * @brief 表示为释放内存
     */
    bool free(uint32_t size)
    {
        if (allocated_size_ >= size) {
            head_ = (head_ + size) % total_size_;
            allocated_size_ -= size;
            return true;
        }
        
        return false;
    }

    uint32_t getHead() const { return head_; }
    uint32_t getSize() const { return allocated_size_; }
    uint32_t getTail() const { return (head_ + allocated_size_) % total_size_; }
private:
    uint32_t head_{};
    uint32_t allocated_size_{};
    uint32_t total_size_{};
};

} // San