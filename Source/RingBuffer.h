#pragma once

#include<array>


template
<std::size_t size_>
class RingBuffer
{
    using array = std::array<float, size_>;
public:
    RingBuffer() = default;
    ~RingBuffer() = default;

    void push(float sample)
    {
        m_samples[m_last_idx++] = sample;
        m_last_idx %= size_;
        if (m_last_idx == 0)
            is_circle = true;
    }

    std::size_t size()
    {
        return is_circle ? size_ : m_last_idx;
    }

    float at(std::size_t idx)
    {
        return m_samples[(m_last_idx + 1 + idx) % size_];
    }

    auto begin()
    {
        return m_samples.begin();
    }

    auto end()
    {
        return m_samples.end();
    }

private:
    array m_samples{ 0.f };
    std::size_t m_last_idx{ 0 };

    bool is_circle{ false };
};