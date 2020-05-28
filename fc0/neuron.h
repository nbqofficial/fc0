#pragma once

#include <iostream>

// activation functions
#define F_SIGM 1
#define F_RELU 2
#define F_TANH 3

class Neuron
{
	private:

		double value;
		double actValue;
		double derValue;
		int activationFunction;

	public:

		void Display()
		{
			printf("\t[ Val: %f  Act: %f  Der: %f Fn: %d ]\n", value, actValue, derValue, activationFunction);
		}

		void Activate()
		{
			switch (activationFunction)
			{
			case F_SIGM:
				actValue = 1 / (1 + exp(-value));
				break;
			case F_RELU:
				if (value > 0)
				{
					actValue = value;
				}
				else
				{
					actValue = 0;
				}
				break;
			case F_TANH:
				actValue = tanh(value);
				break;
			default:
				actValue = 1 / (1 + exp(-value));
				break;
			}
		}

		void Derive()
		{
			switch (activationFunction)
			{
			case F_SIGM:
				derValue = actValue * (1 - actValue);
				break;
			case F_RELU:
				if (value > 0)
				{
					derValue = 1;
				}
				else
				{
					derValue = 0;
				}
				break;
			case F_TANH:
				derValue = 1.0 - (actValue * actValue);
				break;
			default:
				derValue = actValue * (1 - actValue);
				break;
			}




		}

		void SetValue(double value)
		{
			this->value = value;
			Activate();
			Derive();
		}

		double GetValue()
		{
			return value;
		}

		double GetActValue()
		{
			return actValue;
		}

		double GetDerValue()
		{
			return derValue;
		}

		Neuron(double value, int activationFunction)
		{
			this->activationFunction = activationFunction;
			SetValue(value);
		}

		~Neuron()
		{
			value = 0;
			actValue = 0;
			derValue = 0;
			activationFunction = 0;
		}
};