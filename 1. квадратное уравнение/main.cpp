/*
 * ���������, �������� ��������� ax^2 + bx + c = 0.
 * ����� �� ���� ���������� ����� ���� ����� ����,
 * ��������� � �� ����, ��� ������������ ��������
 * ���������� ����������. �� � �� �� � ���.
 */

/* QUESTION - �� ������� �� ����� ������������?
� ��� �� ������ ��������� ������? */

//-----------------------------------v-includ'� � ����������-v-------------------------------------
#include "TXLib.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

enum root_number
{
    ZERO,
    ONE,
    TWO,
    INFTY,
}; // enum ���������� ��������� ������

typedef struct
{
    enum root_number rnum;
    double x1;
    double x2;
    /* x1 � x2 - �����. ������� ����������, ��� ������ ����
    ������������� ���� <= 2. ��������������, ���
    ���� ������ ����, �� �� �������� � x1, ���� ������ ���,
    �� � x1 �������. */
} sSolution; // � ����� ��������� ��������� �������
typedef struct
{
    double a;
    double b;
    double c;
} sParams; // � ����� ��������� ��������� ��������� ���������

#define EPS 1e-6
#define eq(a, b) (fabs((a) - (b)) < EPS)
//-----------------------------------^-includ'� � ����������-^-------------------------------------

int input(int argc, char *argv[], sParams* params); // ��������� ��������� ���������
sSolution deg2(sParams params);        // ������ ��������� ax^2 + bx +c = 0
void fix_zero(sSolution *solution);   // ���������� -0
void output(sSolution solution);       // ������� �������

int main(int argc, char *argv[])
{

    sParams params = {.0, .0, .0};
    if (!input(argc, argv, &params))
        return -1;
    sSolution solution = deg2(params);
    fix_zero(&solution);
    output(solution);

    return 0;
}

//---------------------------------------v-���� � �����-v------------------------------------------
int input_cl(int argc, char *argv[], sParams* params); // ��������� ��������� ��������� ������.
int input(int argc, char *argv[], sParams* params)
/*
 * ��������� ��������� ���������.
 *
 * ��������� ������� ��� ����� ���� �� �������,
 * ���� � ���������� ��������� ������.
 * ������� ������, ����� � ������� ��������
 * ��� - �� ������� ���������.
 *
 * ��������� argc, argv � ��������� ��� ������ ����������.
 * ����������1 � ������ ������, ����� 0.
 */
{
    assert(params!=NULL);

    if (argc > 1)
        return input_cl(argc, argv, params);
    printf("������� ������������ - ��� �����:\n");
    if (scanf("%lf %lf %lf", &params->a, &params->b, &params->c) < 3)
    {
        printf("��������� ������� ������� �������");
        return 0;
    }
    return 1;
}

int input_cl(int argc, char *argv[], sParams* params)
/*
 * ��������� ��������� ��������� ������.
 *
 * ��������� ������� ������ ��� �����. ������� ������!
 *
 * ��������� argc, argv � ��������� ��� ������ ����������.
 * ����������1 � ������ ������, ����� 0.
 */
{
    assert(params!=NULL);

    if (argc < 4)
    {
        printf("������������ ���������� ��������� ������");
        return 0;
    }

    char * p = NULL;

    params->a = strtod(argv[1],&p);
    if (*p != '\0')
        goto NaN_error;
    params->b = strtod(argv[2],&p);
    if (*p != '\0')
        goto NaN_error;
    params->c = strtod(argv[3],&p);
    if (*p != '\0')
        goto NaN_error;

    return 1;

    NaN_error:
        printf("��������� ��������� ������ ������� �������");
        return 0;
}

void fix_zero(sSolution *solution) // FIXME - �� ����� �������� ����� �����?
/*sParams* params
 * ���������� -0.
 *
 * � ��������� ������� � ����� ������������
 * ������������� ����. ���������� �����, �� ���
 * �������� ���������.
 *
 * ��������� ��������� �� ��������� � ������� �
 * �������� -0.0 �� 0.0 .
 */
{
    if (eq(solution->x1, .0))
        solution->x1 = .0;
    if (eq(solution->x2, .0))
        solution->x2 = .0;
}

void output(sSolution solution)
/*
 * ������� �������.
 *
 * ����� ������ ���� �������� � �������, ���
 * �����������. ������� � ��������� �� ��������.
 *
 * ��������� ������� � ���� sSolution,
 * ������ �� ����������.
 */
{
    printf("� ��������� ");

    switch (solution.rnum)
    {
    case ZERO:
        printf("��� ������.\n");
        break;
    case ONE:
        printf("1 ������: %f.\n", solution.x1);
        break;
    case TWO:
        printf("2 �����: %f, %f.\n", solution.x1, solution.x2);
        break;
    case INFTY:
        printf("���������� ����� ������.");
        break;
    default:
        printf("\n ��������� ���-�� ������.");
        break;
    }
}
//---------------------------------------^-���� � �����-^------------------------------------------

//-------------------------------------v-������� ���������-v---------------------------------------
sSolution deg1(sParams params); // ������ ��������� ax + b = 0

sSolution deg2(sParams params)
/*
 * ������ ��������� ax^2 + bx + c = 0.
 *
 * ������ ��������� �� ����������� ����������,
 * �. �. �������� a = 0.
 *
 * ��������� ��������� � ���� sParams, ����������
 * ������� � ���� sSolution.
 */
{
    if (eq(params.a, .0))
        return deg1(params);

    double a = params.a;
    double b = params.b;
    double c = params.c;
    double D = b * b - 4 * a * c;

    if (eq(D, .0))
        return (sSolution){ONE, -b / (2 * a), .0};
    if (D < 0)
        return (sSolution){ZERO, .0, .0};
    return (sSolution){TWO, (-b - sqrt(D)) / (2 * a), (-b + sqrt(D)) / (2 * a)};
}

sSolution deg0(sParams params);  // ������ ��������� c = 0

sSolution deg1(sParams params)
/*
 * ������ ��������� bx + c = 0.
 *
 * ������ ��������� �� ����������� ��������,
 * �. �. �������� b = 0.
 *
 * ��������� ��������� � ���� sParams, ����������
 * ������� � ���� sSolution.
 */
{

    if (eq(params.b, .0))
        return deg0(params);

    double b = params.b;
    double c = params.c;
    return (sSolution){ONE, -c / b, .0};
}

sSolution deg0(sParams params)
/*
 * ������ ��������� c = 0.
 *
 * ������ c  ����� ���� �����.
 *
 * ��������� ��������� � ���� sParams, ����������
 * ������� � ���� sSolution.
 */
{
    return (eq(params.c, .0)) ? (sSolution){INFTY, .0, .0} : (sSolution){ZERO, .0, .0};
    // QUESTION - ������ ���������� ����?
}
//-------------------------------------^-������� ���������-^---------------------------------------

