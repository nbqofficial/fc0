#pragma once

#include <vector>
#include "neuron.h"
#include "matrix.h"

class Layer
{
	private:

		int numOfNeurons;
		std::vector<Neuron> neurons;

	public:

		void Display()
		{

			for (int i = 0; i < numOfNeurons; i++)
			{
				printf("Neuron %d:", i);
				neurons[i].Display();
			}
			printf("\n");
		}

		void SetValue(int index, double value)
		{
			neurons[index].SetValue(value);
		}

		std::vector<Neuron> GetNeurons()
		{
			return neurons;
		}

		Matrix ValuesToMatrix()
		{
			Matrix m(1, neurons.size(), false);
			for (int i = 0; i < neurons.size(); i++)
			{
				m.SetValue(0, i, neurons[i].GetValue());
			}
			return m;
		}

		Matrix ActivatedValuesToMatrix()
		{
			Matrix m(1, neurons.size(), false);
			for (int i = 0; i < neurons.size(); i++)
			{
				m.SetValue(0, i, neurons[i].GetActValue());
			}
			return m;
		}

		Matrix DerivedValuesToMatrix()
		{
			Matrix m(1, neurons.size(), false);
			for (int i = 0; i < neurons.size(); i++)
			{
				m.SetValue(0, i, neurons[i].GetDerValue());
			}
			return m;
		}

		Layer(int numOfNeurons, int activationFunction)
		{
			this->numOfNeurons = numOfNeurons;
			for (int i = 0; i < numOfNeurons; i++)
			{
				neurons.push_back({ 0.0, activationFunction });
			}
		}

		~Layer()
		{
			numOfNeurons = 0;
			neurons.clear();
		}
};
