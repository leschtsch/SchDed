/*
 * ���������, �������� ��������� ax^2 + bx + c = 0.
 * ����� �� ���� ���������� ����� ���� ����� ����,
 * ��������� � �� ����, ��� ������������ ��������
 * ���������� ����������. �� � �� �� � ���.
 */
// QUESTION - �� ����� ������������� � �� �������?
//-------------------------------------------v-�����-v---------------------------------------------
#include "TXLib.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

const int INFTY = -1; // �������� ��� ������������� ������
const double EPS = 1e-6; //  ��������

int cmp_double(double a, double b); // ����� �� ��� �����

typedef struct
{
    int rnum;
    double x1; // x1 � x2 - �����. ��� ����� - x1 < x2.
    double x2; //���� ������ - �� � x1.
} sSolution; // � ����� ��������� ��������� �������

typedef struct
{
    double a;
    double b;
    double c;
} sParams; // � ����� ��������� ��������� ��������� ���������

//-------------------------------------------^-�����-^---------------------------------------------

//-----------------------------------v-main � ���������� ��-v--------------------------------------
int input(int argc, char *argv[], sParams* params); // ��������� ��������� ���������

// TODO - ����� ����
int solve_general(sParams params, sSolution* solution);
void fix_zero(sSolution *solution);   // ���������� -0

void output(sSolution solution);       // ������� �������

int main(int argc, char *argv[])
{
    sParams params = {.0, .0, .0};
    if (!input(argc, argv, &params))
        return -1;

    sSolution solution = {0, .0, .0};
    solve_general(params, &solution);
    fix_zero(&solution);
    output(solution);

    return 0;
}
//-----------------------------------^-main � ���������� ��-^--------------------------------------

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
        printf("��������� ������� �������");
        return 0;
    }
    return 1; //TODO - ��������� ������, 0 - ��� ��
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
        return 1;
    }

    char * p = NULL;

    params->a = strtod(argv[1],&p);
    if (*p != '\0' || p==argv[1])
        goto NaN_error;
    params->b = strtod(argv[2],&p);
    if (*p != '\0' || p==argv[2])
        goto NaN_error;
    params->c = strtod(argv[3],&p);
    if (*p != '\0' || p==argv[3])
        goto NaN_error;

    return 1;

    NaN_error:
        printf("��������� ��������� ������ ������� �������");
        return 0;
}

void fix_zero(sSolution *solution)
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
    if (!cmp_double(solution->x1, .0))
        solution->x1 = .0;
    if (!cmp_double(solution->x2, .0))
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
    case 0:
        printf("��� ������.\n");
        break;
    case 1:
        printf("1 ������: %f.\n", solution.x1);
        break;
    case 2:
        printf("2 �����: %f, %f.\n", solution.x1, solution.x2);
        break;
    case INFTY:
        printf("���������� ����� ������.\n");
        break;
    default:
        fprintf(stderr,"\nERROR: main(): solution.rnum == %d\n", solution.rnum);
        break;
    }
}
//---------------------------------------^-���� � �����-^------------------------------------------

//-------------------------------------v-������� ���������-v---------------------------------------
int solve_deg2(sParams params, sSolution* solution); // ������ ��������� ax^2 + bx +c = 0
int solve_deg1(sParams params, sSolution* solution); // ������ ��������� ax + b = 0
int solve_deg0(sParams params, sSolution* solution); // ������ ��������� c = 0

int solve_general(sParams params, sSolution* solution)
{
    if (cmp_double(params.a, 0))
        return solve_deg2(params, solution);
    if (cmp_double(params.b, 0))
        return solve_deg1(params, solution);
    return solve_deg0(params, solution);
}

int solve_deg2(sParams params, sSolution* solution)
/*
 * ������ ��������� ax^2 + bx + c = 0.
 *
 * ���� a = 0, �� ������ �� assert'�
 *
 * ��������� ��������� � ���� sParams � ���������
 * ��� ������ �������, ���������� 0.
 */
{
    assert(cmp_double(params.a, .0));

    double a = params.a;
    double b = params.b;
    double c = params.c;
    double D = b * b - 4 * a * c;

    if (!cmp_double(D, .0))
        *solution = {1, -b / (2 * a), .0};
    else if (D < 0)
        *solution = {0, .0, .0};
    else
        *solution = {2, (-b - sqrt(D)) / (2 * a), (-b + sqrt(D)) / (2 * a)};

    return 0;
}

int solve_deg1(sParams params, sSolution* solution)
/*
 * ������ ��������� bx + c = 0.
 *
 * ���� b = 0, �� ������ �� assert'�
 *
 * ��������� ��������� � ���� sParams � ���������
 * ��� ������ �������, ���������� 0.
 */
{

    assert(!cmp_double(params.a, .0));
    assert(cmp_double(params.b, .0));

    double b = params.b;
    double c = params.c;
    *solution = {1, -c / b, .0};
    return 0;
}

int solve_deg0(sParams params, sSolution* solution)
/*
 * ������ ��������� c = 0.
 *
 * ������ c  ����� ���� �����.
 *
 * ��������� ��������� � ���� sParams � ���������
 * ��� ������ �������, ���������� 0.
 */
{
    assert(!cmp_double(params.a, .0));
    assert(!cmp_double(params.b, .0));

    *solution =  (cmp_double(params.c, .0)) ? (sSolution){0, .0, .0} : (sSolution){INFTY, .0, .0};
    // QUESTION - ��� �� �������� ��� ����������?
    return 0;
}
//-------------------------------------^-������� ���������-^---------------------------------------

//-------------------------------------v-����� (����������)-v--------------------------------------
int cmp_double(double a, double b)
{
    if (fabs(a-b) < EPS)
        return 0;
    return a<b?-1:1;
}
//-------------------------------------^-����� (����������)-^--------------------------------------

