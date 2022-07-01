#ifndef KNAPSACK_NUMBER_HH
#define KNAPSACK_NUMBER_HH
namespace knapsack
{
template <typename Tag, typename Type> struct Number
{
    using value_t = Type;
    value_t value = static_cast<Type>(0);

    Number() = delete;
    Number(const value_t v) : value{v} {};

    Number(const Number &) = default;
    Number &operator=(const Number &) = default;
    Number(Number &&) noexcept = default;
    Number &operator=(Number &&) noexcept = default;

    operator value_t() const
    {
        return value;
    }

    Number &operator--()
    {
        value--;
        return *this;
    }

    Number operator--(int)
    {
        Number tmp(*this);
        operator--();
        return tmp;
    }
};

template <template <typename, typename> class Object, typename Tag, typename Type>
bool operator==(const Object<Tag, Type> &lhs, const Object<Tag, Type> &rhs)
{
    return lhs.value == rhs.value;
}

template <template <typename, typename> class Object, typename Tag, typename Type>
bool operator<(const Object<Tag, Type> &lhs, const Object<Tag, Type> &rhs)
{
    return lhs.value < rhs.value;
}

template <template <typename, typename> class Object, typename Tag, typename Type>
bool operator>(const Object<Tag, Type> &lhs, const Object<Tag, Type> &rhs)
{
    return lhs.value > rhs.value;
}

template <template <typename, typename> class Object, typename Tag, typename Type>
Object<Tag, Type> operator+(const Object<Tag, Type> &lhs, const Object<Tag, Type> &rhs)
{
    return {lhs.value + rhs.value};
}

template <typename Tag> using Decimal = Number<Tag, long double>;
using Weight = Decimal<struct WeightTag>;
using Value = Decimal<struct ValueTag>;
using Ratio = Decimal<struct RatioTag>;

template <typename Tag> using NaturalNumbers = Number<Tag, unsigned long long>;
using Iteration = Decimal<struct IterationTag>;
using Temperature = Decimal<struct TemperatureTag>;
using AmountOfChromosomes = NaturalNumbers<struct AmountOfChromosomesTag>;
using ProbabilityOfMutation = Decimal<struct ProbabilityOfMutationTag>;

} // namespace knapsack
#endif // KNAPSACK_NUMBER_HH
