/**
 * @file dynamic_array_test.cpp
 * @author Chase Geigle
 * @date Summer 2014
 */

#include "dynamic_array.h"
#include "moveonly.h"
#include <cassert>
#include <type_traits>
#include <memory>

using namespace cs225;

void test_empty_array()
{
    dynamic_array<int> empty;
    assert(empty.size() == 0);
    try
    {
        empty.at(0) = 5;
    }
    catch (const std::out_of_range&)
    {
        return;
    }
    throw std::runtime_error{"index out of bounds exception not thrown!"};
}

void test_sized_array()
{
    dynamic_array<int> sized{5};
    assert(sized.size() == 5);
    sized[0] = 0;
    sized[1] = 2;
    sized[2] = 4;

    try
    {
        sized.at(7) = 12;
    }
    catch (const std::out_of_range&)
    {
        return;
    }
    throw std::runtime_error{"index out of bounds exception not thrown!"};
}

void test_copy_construction()
{
    dynamic_array<uint64_t> arr{4};
    for (uint64_t i = 0; i < arr.size(); ++i)
        arr[i] = i * 2;

    dynamic_array<uint64_t> copy{arr};
    assert(copy.size() == 4);
    for (uint64_t i = 0; i < copy.size(); ++i)
        assert(copy.at(i) == arr.at(i));

    assert(copy.size() == arr.size());
}

void test_move_construction()
{
    dynamic_array<uint64_t> arr{4};
    for (uint64_t i = 0; i < arr.size(); ++i)
        arr[i] = i * 2;

    dynamic_array<uint64_t> mvd{std::move(arr)};
    assert(arr.size() == 0);
    assert(mvd.size() == 4);
    for (uint64_t i = 0; i < mvd.size(); ++i)
        assert(mvd.at(i) == i * 2);

    try
    {
        arr.at(2) = 1;
    }
    catch (const std::out_of_range&)
    {
        return;
    }
    throw std::runtime_error{"index out of bounds exception not thrown!"};
}

void test_copy_assignment()
{
    dynamic_array<uint64_t> arr{4};
    for (uint64_t i = 0; i < arr.size(); ++i)
        arr[i] = i * 2;

    dynamic_array<uint64_t> copy{5};
    for (uint64_t i = 0; i < copy.size(); ++i)
        copy[i] = 5;

    copy = arr;
    assert(arr.size() == 4);
    assert(copy.size() == arr.size());
    for (uint64_t i = 0; i < copy.size(); ++i)
        assert(copy.at(i) == arr.at(i));

    try
    {
        copy.at(4) = 1;
    }
    catch (const std::out_of_range&)
    {
        return;
    }
    throw std::runtime_error{"index out of bounds exception not thrown!"};
}

void test_move_assignment()
{
    dynamic_array<uint64_t> arr{4};
    for (uint64_t i = 0; i < arr.size(); ++i)
        arr[i] = i * 2;

    dynamic_array<uint64_t> mvd{14};
    for (uint64_t i = 0; i < mvd.size(); ++i)
        mvd[i] = 42;

    mvd = std::move(arr);
    assert(arr.size() == 0);
    assert(mvd.size() == 4);
    for (uint64_t i = 0; i < mvd.size(); ++i)
        assert(mvd.at(i) == i * 2);

    try
    {
        mvd.at(10) = 1;
    }
    catch (const std::out_of_range&)
    {
        return;
    }
    throw std::runtime_error{"index out of bounds exception not thrown!"};
}

void test_clear()
{
    dynamic_array<uint64_t> arr{4};
    for (uint64_t i = 0; i < arr.size(); ++i)
        arr[i] = i * 2;
    assert(arr.size() == 4);
    arr.clear();
    assert(arr.size() == 0);
    try
    {
        arr.at(1) = 2;
    }
    catch (const std::out_of_range&)
    {
        return;
    }
    throw std::runtime_error{"index out of bounds exception not thrown!"};
}

void test_swap()
{
    dynamic_array<uint64_t> arr{4};
    for (uint64_t i = 0; i < arr.size(); ++i)
        arr[i] = i * 2;

    dynamic_array<uint64_t> other{14};
    for (uint64_t i = 0; i < other.size(); ++i)
        other[i] = 42;

    arr.swap(other);
    assert(arr.size() == 14);
    assert(other.size() == 4);

    for (uint64_t i = 0; i < arr.size(); ++i)
        assert(arr.at(i) == 42);
    for (uint64_t i = 0; i < other.size(); ++i)
        assert(other.at(i) == i * 2);
}

void test_resize_smaller()
{
    dynamic_array<uint64_t> arr{14};
    for (uint64_t i = 0; i < arr.size(); ++i)
        arr[i] = i * i;

    arr.resize(3);
    assert(arr.size() == 3);
    for (uint64_t i = 0; i < arr.size(); ++i)
        assert(arr.at(i) == i * i);
}

void test_resize_smaller_moveonly()
{
    dynamic_array<moveonly> arr{14};
    for (uint64_t i = 0; i < arr.size(); ++i)
        arr[i] = moveonly{i * i};

    arr.resize(3);
    assert(arr.size() == 3);
    for (uint64_t i = 0; i < arr.size(); ++i)
        assert(arr.at(i).get() == i * i);
}

void test_resize_larger()
{
    dynamic_array<uint64_t> arr{14};
    for (uint64_t i = 0; i < arr.size(); ++i)
        arr[i] = i * i;

    arr.resize(20);
    assert(arr.size() == 20);

    for (uint64_t i = 0; i < 14; ++i)
        assert(arr.at(i) == i * i);
}

void test_resize_larger_moveonly()
{
    dynamic_array<moveonly> arr{14};
    for (uint64_t i = 0; i < arr.size(); ++i)
        arr[i] = moveonly{i * i};

    arr.resize(20);
    assert(arr.size() == 20);

    for (uint64_t i = 0; i < 14; ++i)
        assert(arr.at(i).get() == i * i);
}

int main()
{
    test_empty_array();
    test_sized_array();
    test_copy_construction();
    test_move_construction();
    test_copy_assignment();
    test_move_assignment();
    test_clear();
    test_swap();
    test_resize_smaller();
    test_resize_larger();
    return 0;
}
