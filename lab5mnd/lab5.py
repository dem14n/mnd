# Красновський Олексій
# Варіант 115:
# x1_min = -1, x1_max = 2,
# x2_min = -9, x2_max = 6,
# x3_min = -5, x3_max = 8
# y_max = 200 + xc_max
# y_min = 200 + xc_min

from random import *
from pprint import pprint
from math import sqrt
from scipy.stats import f
from scipy.stats import t as t_check
import sklearn.linear_model as lm
N, d, l = 15, 8, 1.215
print("y` = b0 + b1*x1 + b2*x2 + b3*x3 + b12*x1*x2 + b13x1*x3 + b23*x2*x3 + b123*x1*x2*x3 + b11*x1**2 + b22*x2**2 + b33*x3**2")
def create_mat(N, m):
    matrix_X = [[-1, 2], [-9, 6], [-5, 8]]
    plan_matrix = [[-1, -1, -1], [-1, -1, 1], [-1, 1, -1], [-1, 1, 1], [1, -1, -1], [1, -1, 1], [1, 1, -1], [1, 1, 1], [-1.215, 0, 0], [1.215, 0, 0], [0, -1.215, 0], [0, 1.215, 0], [0, 0, -1.215], [0, 0, 1.215], [0, 0, 0]]
    nat_matrix = [[-1, -1, -1], [-1, -1, 1], [-1, 1, -1], [-1, 1, 1], [1, -1, -1], [1, -1, 1], [1, 1, -1], [1, 1, 1],
              [-1.215, 0, 0], [1.215, 0, 0], [0, -1.215, 0], [0, 1.215, 0], [0, 0, -1.215], [0, 0, 1.215], [0, 0, 0]]
    x_min_max = [sum(matrix_X[i][k] for i in range(3))/3 for k in range(2)]
    y_min_max = [int(200 + x_min_max[i]) for i in range(2)]
    print('Задана матриця Х:\n', matrix_X)
    print('Xср_min та Xcp_max:\n', x_min_max, '\nY_min та Y_max:\n', y_min_max, '\nМатриця Y:')
    mat_Y = [[randint(y_min_max[0], y_min_max[1]) for i in range(m)] for k in range(N)]
    pprint(mat_Y)
    average_Y = [sum(mat_Y[k1])/m for k1 in range(N)]
    print('Середні значення Y:\n', average_Y, '\nНормована матриця Х:')
    mat_X0i = [sum(matrix_X[i]) / 2 for i in range(3)]
    mat_dX = [matrix_X[i][1] - mat_X0i[i] for i in range(3)]
    mat_X = [[], [], [], [], [], [], [], [], [], [], [], [], [], [], []]
    for i in range(15):
        for j in range(3, 10):
                nat_matrix[i].append(nat_matrix[i][0] * nat_matrix[i][1])
                nat_matrix[i].append(nat_matrix[i][0] * nat_matrix[i][2])
                nat_matrix[i].append(nat_matrix[i][1] * nat_matrix[i][2])
                nat_matrix[i].append(nat_matrix[i][0] * nat_matrix[i][1] * nat_matrix[i][2])
                nat_matrix[i].append(nat_matrix[i][0] ** 2)
                nat_matrix[i].append(nat_matrix[i][1] ** 2)
                nat_matrix[i].append(nat_matrix[i][2] ** 2)
                break
    for i in range(15):
        nat_matrix[i].insert(0, 1)
    pprint(nat_matrix)
    for i in range(8):
        for j in range(10):
            if j < 3:
                if plan_matrix[i][j] == -1:
                    mat_X[i].append(matrix_X[j][0])
                else:
                    mat_X[i].append(matrix_X[j][1])
            if j > 3:
                mat_X[i].append(mat_X[i][0] * mat_X[i][1])
                mat_X[i].append(mat_X[i][0] * mat_X[i][2])
                mat_X[i].append(mat_X[i][1] * mat_X[i][2])
                mat_X[i].append(mat_X[i][0] * mat_X[i][1] * mat_X[i][2])
                mat_X[i].append(mat_X[i][0] ** 2)
                mat_X[i].append(mat_X[i][1] ** 2)
                mat_X[i].append(mat_X[i][2] ** 2)
                break

    for i in range(8, 15):
        for j in range(10):
            if j < 3:
                if plan_matrix[i][j] == 0:
                    mat_X[i].append(mat_X0i[j])
                else:
                    mat_X[i].append(plan_matrix[i][j] * mat_dX[j] + mat_X0i[j])
            else:
                mat_X[i].append(mat_X[i][0] * mat_X[i][1])
                mat_X[i].append(mat_X[i][0] * mat_X[i][2])
                mat_X[i].append(mat_X[i][1] * mat_X[i][2])
                mat_X[i].append(mat_X[i][0] * mat_X[i][1] * mat_X[i][2])
                mat_X[i].append(mat_X[i][0] ** 2)
                mat_X[i].append(mat_X[i][1] ** 2)
                mat_X[i].append(mat_X[i][2] ** 2)
                break

    return (mat_X, mat_Y, average_Y, nat_matrix)

def coef_b(x, y):
    for i in range(15):
        x[i].insert(0, 1)
    print('Нормалізована матриця Х:')
    pprint(x, width=150)
    skm = lm.LinearRegression(fit_intercept=False)
    skm.fit(x, y)
    b = skm.coef_
    b = [round(i, 3) for i in b]
    print(b)

    return b


def check(average_Y, mat_Y, tran1, blist, matt_fullX, m):
    global b1
    d = 11
    b = 0
    b1 = 0
    d1 = 11
    mat_disY = [sum([((k1 - average_Y[j]) ** 2) for k1 in mat_Y[j]]) / m for j in range(N)]
    print("Дисперсії по рядках:\n", mat_disY)
    print('-------------------------------------------------------------------------')
    print('ПЕРЕВІРКА ОДНОРІДНОСТІ ДИСПЕРСІЇ ЗА КРИТЕРІЄМ КОХРЕНА:')
    if max(mat_disY) / sum(mat_disY) < 0.7679:
        print('Дисперсія однорідна')
    else:
        print('Дисперсія неоднорідна')
        m += 1
        main(N, m)
    print('-------------------------------------------------------------------------')
    print('ПЕРЕВІРКА ЗНАЧУЩОСТІ КОЕФІЦІЄНТІВ ЗА КРИТЕРІЄМ СТЬЮДЕНТА:')
    S2b = sum(mat_disY) / N
    S2bs = S2b / (m * N)
    Sbs = sqrt(S2bs)
    print('Sbs:\n', Sbs)
    bb = [sum(average_Y[k] * tran1[i][k] for k in range(N)) / N for i in range(d)]
    t = [abs(bb[i]) / Sbs for i in range(d1)]
    print('bi:\n', bb, '\nti:\n', t)
    f1, f2 = m - 1, N
    f3 = f1 * f2
    for i in range(d1):
        if t[i] < t_check.ppf(q=0.975, df=f3):
            blist[i] = 0
            d -= 1
            b += 1
            print('Виключаємо з рівняння коефіціент b', i)
    y_reg = [
        blist[0] * matt_fullX[i][0] + blist[1] * matt_fullX[i][1] + blist[2] * matt_fullX[i][2] + blist[3] * matt_fullX[i][3] + blist[4] *
        matt_fullX[i][4] + blist[5] * matt_fullX[i][5] + blist[6] * matt_fullX[i][6] + blist[7] * matt_fullX[i][7] + blist[8] * matt_fullX[i][8] + blist[9] * matt_fullX[i][9] + blist[10] * matt_fullX[i][10] for i
        in range(N)]
    print('Значення рівнянь регресій:\n', y_reg)
    print('-------------------------------------------------------------------------')
    print('ПЕРЕВІРКА АДЕКВАТНОСТІ ЗА КРИТЕРІЄМ ФІШЕРА:')
    f4 = N - d
    Sad = (m / (N - d)) * int(sum(y_reg[i] - average_Y[i] for i in range(N)) ** 2)
    Fp = Sad / S2b
    b1 += b
    print('Кількість значимих коефіціентів:\n', d, '\nFp:\n', Fp)
    if Fp > f.ppf(q=0.95, dfn=f4, dfd=f3):
        print('Рівняння регресії неадекватно оригіналу при рівні значимості 0.05')
    else:
        print('Рівняння регресії адекватно оригіналу при рівні значимості 0.05')


def main(N, m):
    x, mat_Y, average_Y, nat_matrix = create_mat(N, m)
    tran1 = [list(i) for i in zip(*nat_matrix)]
    b = coef_b(x, average_Y)
    check(average_Y, mat_Y, tran1, b, x, m)


main(15, 3)



