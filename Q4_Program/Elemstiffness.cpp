#include "B_matrix.hpp"
#include "ja.hpp"
#include <malloc.h>
#include<vector>
//double** ElementStiffness(double E, double u, double h, double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4)
//{
//	//				��Ԫ�նȾ���Ϊ8x8����
//	//				E ������ģ����u �����ɱȣ�h�����
//	//				���Ծ��� D
//
//	double D[3][3] = { E / (1 - u * u) ,E * u / (1 - u * u) , 0, E * u / (1 - u * u) ,E / (1 - u * u) , 0, 0, 0,(1 - u) * E / (2 * (1 - u * u)) };
//
//
//	//				��ʼ����Ԫ�նȾ���
//
//	static double** Ke;		//	8x8����
//
//	Ke = (double**)malloc(8 * sizeof(double));
//	for (int i = 0; i < 8; i++)
//	{
//		Ke[i] = (double*)malloc(8 * sizeof(double));
//		for (int j = 0; j < 8; j++)
//		{
//			Ke[i][j] = 0;
//		}
//
//	}
//
//	//				��˹����
//
//	int W[2] = { 1,1 };																	//��Ȩϵ��
//	double x[2] = { -0.577350 , 0.577350 };	//���ֵ�
//
//	//cout << x[1] << endl;		//		����
//
//	double B[3][8], Bt[8][3];				//  ���弸�ξ�����ת��
//	double J[2][2];							//  �����ſɱȾ���
//	double detJ = 0;
//	double BtD[8][3];
//
//	//				��ʼ��BtD
//
//	for (int i = 0; i < 8; i++)
//	{
//		for (int j = 0; j < 3; j++)
//		{
//			BtD[i][j] = 0;
//		}
//	}
//
//	//		���ĸ����ֵ���и�˹���֣���ⵥԪ�նȾ���
//
//	for (int a = 0; a < 2; a++)
//	{
//		for (int b = 0; b < 2; b++)
//		{
//
//			//				��ʼ��BtD
//			for (int i = 0; i < 8; i++)
//			{
//				for (int j = 0; j < 3; j++)
//				{
//					BtD[i][j] = 0;
//				}
//			}
//
//			//				�󼸺ξ���B����ת�þ���
//
//			for (int s = 0; s < 3; s++)
//			{
//				for (int k = 0; k < 8; k++)
//				{
//					B[s][k] = *(*(BMatrix(x1, y1, x2, y2, x3, y3, x4, y4, x[a], x[b]) + s) + k);
//				}
//			}
//			//	B ת�þ���Bt
//
//			for (int s = 0; s < 3; s++)
//			{
//				for (int k = 0; k < 8; k++)
//				{
//
//					Bt[k][s] = B[s][k];
//
//				}
//			}
//
//			//			���ſɱȾ��� J	�Լ�detJ
//
//			for (int i = 0; i < 2; i++)
//			{
//				for (int j = 0; j < 2; j++)
//				{
//					J[i][j] = *(*(Jacobi(x1, y1, x2, y2, x3, y3, x4, y4, x[a], x[b]) + i) + j);
//				}
//			}
//			detJ = J[0][0] * J[1][1] - J[1][0] * J[0][1];
//			//cout << detJ << endl;
//
//			//			B��ת�á�D  BtD
//
//			for (int i = 0; i < 8; i++)
//			{
//				for (int j = 0; j < 3; j++)
//				{
//					for (int k = 0; k < 3; k++)
//					{
//						BtD[i][j] = BtD[i][j] + Bt[i][k] * D[k][j];
//					}
//
//				}
//
//			}
//
//			//			��Ԫ�նȾ���
//
//
//			for (int i = 0; i < 8; i++)
//			{
//				for (int j = 0; j < 8; j++)
//				{
//					for (int k = 0; k < 3; k++)
//					{
//						Ke[i][j] = Ke[i][j] + BtD[i][k] * B[k][j] * detJ * h * W[a] * W[b];
//
//					}
//
//				}
//
//			}
//
//
//		}
//	}
//
//	return Ke;
//
//}





vector<vector<double>> ElementStiffness(double E, double u, double h, double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4)
{
	//				��Ԫ�նȾ���Ϊ8x8����
	//				E ������ģ����u �����ɱȣ�h�����
	//				���Ծ��� D

	double D[3][3] = { E / (1 - u * u) ,E * u / (1 - u * u) , 0, E * u / (1 - u * u) ,E / (1 - u * u) , 0, 0, 0,(1 - u) * E / (2 * (1 - u * u)) };


	//				��ʼ����Ԫ�նȾ���

	vector<vector<double>> Ke;		//	����һ����ά����

	
	for (int i = 0; i < 8; i++)    //��ʼ��
	{
		for (int j = 0; j < 8; j++)
		{
			Ke[i][j] = 0;
		}

	}

	//				��˹����

	int W[2] = { 1,1 };																	//��Ȩϵ��
	double x[2] = { -0.577350 , 0.577350 };	//���ֵ�

	//cout << x[1] << endl;		//		����

	double B[3][8], Bt[8][3];				//  ���弸�ξ�����ת��
	double J[2][2];							//  �����ſɱȾ���
	double detJ = 0;
	double BtD[8][3];

	//				��ʼ��BtD

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			BtD[i][j] = 0;
		}
	}

	//		���ĸ����ֵ���и�˹���֣���ⵥԪ�նȾ���

	for (int a = 0; a < 2; a++)
	{
		for (int b = 0; b < 2; b++)
		{

			//				��ʼ��BtD
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					BtD[i][j] = 0;
				}
			}

			//				�󼸺ξ���B����ת�þ���
			vector<vector<double>>bmatrix = BMatrix(x1, y1, x2, y2, x3, y3, x4, y4, x[a], x[b]);
			for (int s = 0; s < 3; s++)
			{
				for (int k = 0; k < 8; k++)
				{
					B[s][k] = bmatrix[s][k];
				}
			}
			//	B ת�þ���Bt

			for (int s = 0; s < 3; s++)
			{
				for (int k = 0; k < 8; k++)
				{

					Bt[k][s] = B[s][k];

				}
			}

			//			���ſɱȾ��� J	�Լ�detJ
			vector<vector<double>>Ja = Jacobi(x1, y1, x2, y2, x3, y3, x4, y4, x[a], x[b]);
			for (int i = 0; i < 2; i++)
			{
				for (int j = 0; j < 2; j++)
				{
					J[i][j] = Ja[i][j];
				}
			}
			detJ = J[0][0] * J[1][1] - J[1][0] * J[0][1];
			//cout << detJ << endl;

			//			B��ת�á�D  BtD

			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					for (int k = 0; k < 3; k++)
					{
						BtD[i][j] = BtD[i][j] + Bt[i][k] * D[k][j];
					}

				}

			}

			//			��Ԫ�նȾ���


			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					for (int k = 0; k < 3; k++)
					{
						Ke[i][j] = Ke[i][j] + BtD[i][k] * B[k][j] * detJ * h * W[a] * W[b];

					}

				}

			}


		}
	}

	return Ke;

}