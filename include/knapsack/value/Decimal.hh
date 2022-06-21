#ifndef KNAPSACK_DECIMAL_HH
#define KNAPSACK_DECIMAL_HH
namespace knapsack
{
template <typename Tag> struct Decimal
{
    using value_t = long double;
    value_t value = 0.0L;

    Decimal() = delete;
    Decimal(const value_t v) : value{v} {};

    Decimal(const Decimal &) = default;
    Decimal &operator=(const Decimal &) = default;
    Decimal(Decimal &&) = default;
    Decimal &operator=(Decimal &&) = default;

    bool operator==(const Decimal<Tag> &rhs)
    {
        return value == rhs.value;
    }

    bool operator<(const Decimal<Tag> &rhs)
    {
        return value < rhs.value;
    }

    bool operator>(const Decimal<Tag> &rhs)
    {
        return value > rhs.value;
    }

    operator value_t() const
    {
        return value;
    }
};

template <typename Tag> Decimal<Tag> operator+(const Decimal<Tag> &lhs, const Decimal<Tag> &rhs)
{
    return {lhs.value + rhs.value};
}

using Weight = Decimal<struct WeightTag>;
using Value = Decimal<struct ValueTag>;
using Ratio = Decimal<struct RatioTag>;
} // namespace knapsack
#endif // KNAPSACK_DECIMAL_HH
