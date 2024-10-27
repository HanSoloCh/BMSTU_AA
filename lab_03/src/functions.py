from ComparisonCounter import *


def linear_search(lst: list, item: int) -> int | None:
    n = len(lst)
    i = 0
    while ComparisonCounter.lt(i, n):
        if ComparisonCounter.eq(lst[i], item):
            return i
        i += 1

    return None


def binary_search(lst: list, item: int) -> int | None:
    left = 0
    right = len(lst) - 1
    while ComparisonCounter.le(left, right):
        mid = (left + right) // 2
        if ComparisonCounter.eq(lst[mid], item):
            return mid

        if ComparisonCounter.lt(item, lst[mid]):
            right = mid - 1
        else:
            left = mid + 1

    return None
