#pragma once

#include <vector>
#include <iostream>
#include <random>

class Matrix
{
	private:

		int numOfRows;
		int numOfColumns;
		std::vector<std::vector<double>> values;

	public:

		void Display()
		{
			for (int i = 0; i < numOfRows; i++)
			{
				for (int j = 0; j < numOfColumns; j++)
				{
					printf("%f\t", values[i][j]);
				}
				printf("\n");
			}
			printf("\n");
		}

		double GetRandom()
		{
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_real_distribution<> dis(-.0001, .0001);
			return dis(gen);
		}

		int GetNumOfRows()
		{
			return numOfRows;
		}

		int GetNumOfColumns()
		{
			return numOfColumns;
		}

		void SetValue(int row, int column, double value)
		{
			values[row][column] = value;
		}

		double GetValue(int row, int column)
		{
			return values[row][column];
		}

		std::vector<std::vector<double>> GetValues()
		{
			return values;
		}

		Matrix Transpose()
		{
			Matrix m(numOfColumns, numOfRows, false);
			for (int i = 0; i < numOfRows; i++)
			{
				for (int j = 0; j < numOfColumns; j++)
				{
					m.SetValue(j, i, GetValue(i, j));
				}
			}
			return m;
		}

		Matrix(int numOfRows, int numOfColumns, bool isRandom)
		{
			this->numOfRows = numOfRows;
			this->numOfColumns = numOfColumns;

			for (int i = 0; i < numOfRows; i++)
			{
				std::vector<double> columnValues;
				for (int j = 0; j < numOfColumns; j++)
				{
					double r = 0.0;
					if (isRandom)
					{
						r = GetRandom();
					}
					columnValues.push_back(r);
				}
				values.push_back(columnValues);
			}
		}

		~Matrix()
		{
			values.clear();
			numOfRows = 0;
			numOfColumns = 0;
		}
};