def levenstein_recursive(s_1, s_2):
    if len(s_1) == 0:
        return len(s_2)

    if len(s_2) == 0:
        return len(s_1)

    if s_1[0] == s_2[0]:
        return levenstein_recursive(s_1[1:], s_2[1:])

    return 1 + min(
               levenstein_recursive(s_1[1:], s_2),
               levenstein_recursive(s_1, s_2[1:]),
               levenstein_recursive(s_1[1:], s_2[1:])
               )


def levenshtein_memoization(s_1, s_2):
    n = len(s_1)
    m = len(s_2)

    mtr = [[0] * (m + 1) for i in range(n + 1)]

    for i in range(m + 1):
        mtr[i][0] = i

    for j in range(n + 1):
        mtr[0][i] = j

    for i in range(1, n + 1):
        for j in range(1, m + 1):
            changeable = 1 if s_1[j - 1] != s_2[i - 1] else 0
            mtr[i][j] = min(mtr[i - 1][j] + 1,
                            mtr[i][j - 1] + 1,
                            mtr[i - 1][j - 1] + changeable)
    return mtr[n][m]


def damerau_levenshtein(s_1, s_2):
    n = len(s_1)
    m = len(s_2)

    mtr = [[0] * (m + 1) for i in range(n + 1)]

    for i in range(m + 1):
        mtr[i][0] = i

    for j in range(n + 1):
        mtr[0][j] = j

    for i in range(len(s_2)):
        for j in range(len(s_1)):
            changeable = 1 if s_1[j - 1] != s_2[i - 1] else 0
            if i > 1 and j > 1 and s_1[j] == s_2[i - 1] and s_1[j - 1] == s_2[i]:
                mtr[i][j] = min(mtr[i - 1][j] + 1,
                                mtr[i][j - 1] + 1,
                                mtr[i - 1][j - 1] + changeable,
                                mtr[i - 2][j - 2] + 1)
            else:
                mtr[i][j] = min(mtr[i - 1][j] + 1,
                                mtr[i][j - 1] + 1,
                                mtr[i - 1][j - 1] + changeable)

    return mtr[n][m]