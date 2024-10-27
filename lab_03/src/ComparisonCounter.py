class ComparisonCounter:
    __count = 0

    @staticmethod
    def start():
        ComparisonCounter.__count = 0

    @staticmethod
    def stop():
        ComparisonCounter.__count = 0

    @staticmethod
    def get_count():
        return ComparisonCounter.__count

    @staticmethod
    def eq(a, b):
        ComparisonCounter.__count += 1
        return a == b

    @staticmethod
    def ne(a, b):
        ComparisonCounter.__count += 1
        return a != b

    @staticmethod
    def gt(a, b):
        ComparisonCounter.__count += 1
        return a > b

    @staticmethod
    def lt(a, b):
        ComparisonCounter.__count += 1
        return a < b

    @staticmethod
    def ge(a, b):
        ComparisonCounter.__count += 1
        return a >= b

    @staticmethod
    def le(a, b):
        ComparisonCounter.__count += 1
        return a <= b
