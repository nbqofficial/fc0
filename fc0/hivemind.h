#pragma once

#include "layer.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <chrono>
#include "json.hpp"

using json = nlohmann::json;

class HiveMind
{
	private:

		std::vector<int> topology;
		std::vector<Layer> layers;
		std::vector<Matrix> weights;
		std::vector<double> input;
		std::vector<double> target;
		std::vector<double> loss;
		std::vector<double> derLoss;
		double totalLoss;
		int topologySize;
		double bias;
		double learningRate;
		double momentum;
		int outputActFunction;
		int hiddenActFunction;
		int epoch;
		std::string hiveName;
		std::string weightsFile;
		std::string inputsFile;
		std::string targetsFile;
		bool displayLoss;

	public:

		void Display(bool bLayers, bool bWeights)
		{
			for (int i = 0; i < layers.size(); i++)
			{
				if (bLayers)
				{
					printf("Layer: %d\n", i);
					if (i == 0)
					{
						Matrix m = layers[i].ValuesToMatrix();
						m.Display();
					}
					else
					{
						Matrix m = layers[i].ActivatedValuesToMatrix();
						m.Display();
					}
				}
				if (bWeights)
				{
					if (i < layers.size() - 1)
					{
						printf("Weights: %d\n", i);
						weights[i].Display();
					}
				}
			}
		}

		void SetInput(std::vector<double> input)
		{
			this->input = input;
			for (int i = 0; i < input.size(); i++)
			{
				layers[0].SetValue(i, input[i]);
			}
		}

		void SetTarget(std::vector<double> target)
		{
			this->target = target;
		}

		double GetTotalLoss()
		{
			return totalLoss;
		}

		Matrix MatrixMultiply(Matrix a, Matrix b)
		{
			Matrix c(a.GetNumOfRows(), b.GetNumOfColumns(), false);
			for (int i = 0; i < a.GetNumOfRows(); i++)
			{
				for (int j = 0; j < b.GetNumOfColumns(); j++)
				{
					for (int k = 0; k < b.GetNumOfRows(); k++)
					{
						double p = a.GetValue(i, k) * b.GetValue(k, j);
						double newVal = c.GetValue(i, j) + p;
						c.SetValue(i, j, newVal);
					}
					c.SetValue(i, j, c.GetValue(i, j));
				}
			}
			return c;
		}

		std::vector<std::vector<double>> GetData(std::string dataFileName)
		{
			std::vector<std::vector<double>> data;

			std::ifstream dataFile(dataFileName);
			if (dataFile.is_open())
			{
				std::string line;
				while (std::getline(dataFile, line))
				{
					std::vector<double> r;
					std::string token;
					std::stringstream ss(line);
					while (std::getline(ss, token, ','))
					{
						r.push_back(std::stod(token));
					}
					data.push_back(r);
				}
				dataFile.close();
			}
			else
			{
				printf("HiveMind() Error: Cannot open data file\n");
				exit(EXIT_FAILURE);
			}
			return data;
		}

		void SaveWeights()
		{
			json j = {};
			std::vector<std::vector<std::vector<double>>> weightSet;
			for (int i = 0; i < weights.size(); i++)
			{
				weightSet.push_back(weights[i].GetValues());
			}
			j["weights"] = weightSet;
			std::ofstream wf(weightsFile);
			if (wf.is_open())
			{
				wf << std::setw(4) << j << std::endl;
				wf.close();
			}
			else
			{
				printf("HiveMind() Error: Cannot open weights file\n");
				exit(EXIT_FAILURE);
			}
			printf("Saving weights\n");
		}

		void LoadWeights()
		{
			std::ifstream wf(weightsFile);
			json j;
			bool isempty = wf.peek() == EOF;

			if (wf.is_open())
			{
				if (!isempty)
				{
					wf >> j;


					std::vector<std::vector<std::vector<double>>> temp = j["weights"];
					for (int i = 0; i < weights.size(); i++)
					{
						for (int r = 0; r < weights[i].GetNumOfRows(); r++)
						{
							for (int c = 0; c < weights[i].GetNumOfColumns(); c++)
							{
								weights[i].SetValue(r, c, temp[i][r][c]);
							}
						}
					}
				}
				else
				{
					SaveWeights();
				}
				wf.close();
			}
			else
			{
				printf("HiveMind() Error: Cannot open weights file\n\n");
				exit(EXIT_FAILURE);
			}
		}

		void LoadConfig(std::string configName)
		{
			std::ifstream cfgFile(configName);

			if (cfgFile.is_open())
			{
				std::string str((std::istreambuf_iterator<char>(cfgFile)),
					std::istreambuf_iterator <char>());

				auto config = json::parse(str);
				this->hiveName = config["name"].get <std::string>();
				this->topology = config["topology"].get <std::vector<int>>();
				this->outputActFunction = config["outputActFunction"];
				this->hiddenActFunction = config["hiddenActFunction"];
				this->learningRate = config["learningRate"];
				this->momentum = config["momentum"];
				this->bias = config["bias"];
				this->epoch = config["epoch"];
				this->displayLoss = config["displayLoss"];
				this->weightsFile = config["weights"].get<std::string>();
				this->inputsFile = config["inputs"].get<std::string>();
				this->targetsFile = config["targets"].get<std::string>();

				cfgFile.close();
			}
			else
			{
				printf("HiveMind() Error: Cannot open config file\n");
				exit(EXIT_FAILURE);
			}
		}

		void CalculateLoss()
		{
			if (target.size() == 0)
			{
				printf("HiveMind() Error: Target vector not initialized\n");
				exit(EXIT_FAILURE);
			}

			if (target.size() != layers[layers.size() - 1].GetNeurons().size())
			{
				printf("HiveMind() Error: Incorrect target vector size\n");
				exit(EXIT_FAILURE);
			}

			totalLoss = 0.0;

			for (int i = 0; i < target.size(); i++)
			{
				double t = target[i];
				double y = layers[layers.size() - 1].GetNeurons()[i].GetActValue();

				loss[i] = 0.5 * pow(abs(t - y), 2);
				derLoss[i] = y - t;
				totalLoss += loss[i];
			}
		}

		void FeedForward()
		{
			for (int i = 0; i < topologySize - 1; i++)
			{
				Matrix a = layers[i].ValuesToMatrix();
				Matrix b = weights[i];
				Matrix c(a.GetNumOfRows(), b.GetNumOfColumns(), false);
				if (i != 0)
				{
					a = layers[i].ActivatedValuesToMatrix();
				}
				c = MatrixMultiply(a, b);
				for (int j = 0; j < c.GetNumOfColumns(); j++)
				{
					layers[i + 1].SetValue(j, c.GetValue(0, j) + bias);
				}
			}
		}

		void BackProp()
		{
			std::vector<Matrix> newWeights;

			// output to hidden
			int indexOutputLayer = topologySize - 1;

			Matrix gradients(1, topology[indexOutputLayer], false);

			Matrix derivedValues = layers[indexOutputLayer].DerivedValuesToMatrix();

			for (int i = 0; i < topology[indexOutputLayer]; i++)
			{
				double e = derLoss[i];
				double y = derivedValues.GetValue(0, i);
				double g = e * y;
				gradients.SetValue(0, i, g);
			}

			Matrix gradientsTransposed = gradients.Transpose();

			Matrix zActivatedVals = layers[indexOutputLayer - 1].ActivatedValuesToMatrix();

			Matrix deltaWeights(gradientsTransposed.GetNumOfRows(),
				gradientsTransposed.GetNumOfColumns(), false);

			deltaWeights = MatrixMultiply(gradientsTransposed, zActivatedVals);

			Matrix tempNewWeights(topology[indexOutputLayer - 1],
				topology[indexOutputLayer], false);

			for (int r = 0; r < topology[indexOutputLayer - 1]; r++) {
				for (int c = 0; c < topology[indexOutputLayer]; c++) {

					double originalValue = weights[indexOutputLayer - 1].GetValue(r, c);
					double deltaValue = deltaWeights.GetValue(c, r);

					originalValue = momentum * originalValue;
					deltaValue = learningRate * deltaValue;

					tempNewWeights.SetValue(r, c, (originalValue - deltaValue));
				}
			}
			newWeights.push_back(tempNewWeights);

			// hidden to input

			for (int i = (indexOutputLayer - 1); i > 0; i--)
			{
				Matrix transposedPWeights = weights[i].Transpose();

				Matrix gradients2(gradients.GetNumOfRows(),
					transposedPWeights.GetNumOfColumns(),
					false);

				gradients2 = MatrixMultiply(gradients, transposedPWeights);

				Matrix hiddenDerived = layers[i].DerivedValuesToMatrix();

				for (int colCounter = 0; colCounter < hiddenDerived.GetNumOfRows(); colCounter++)
				{
					double  g = gradients2.GetValue(0, colCounter) * hiddenDerived.GetValue(0, colCounter);
					gradients2.SetValue(0, colCounter, g);
				}

				if (i == 1)
				{
					zActivatedVals = layers[0].ValuesToMatrix();
				}
				else
				{
					zActivatedVals = layers[i - 1].ActivatedValuesToMatrix();
				}

				Matrix transposedHidden = zActivatedVals.Transpose();

				Matrix deltaWeights2(transposedHidden.GetNumOfRows(),
					gradients2.GetNumOfColumns(),
					false);

				deltaWeights2 = MatrixMultiply(transposedHidden, gradients2);

				Matrix tempNewWeights2(weights[i - 1].GetNumOfRows(),
					weights[i - 1].GetNumOfColumns(),
					false);

				for (int r = 0; r < tempNewWeights2.GetNumOfRows(); r++)
				{
					for (int c = 0; c < tempNewWeights2.GetNumOfColumns(); c++)
					{
						double originalValue = weights[i - 1].GetValue(r, c);
						double deltaValue = deltaWeights2.GetValue(r, c);

						originalValue = momentum * originalValue;
						deltaValue = learningRate * deltaValue;

						tempNewWeights2.SetValue(r, c, (originalValue - deltaValue));
					}
				}
				newWeights.push_back(tempNewWeights2);
			}

			weights.clear();

			std::reverse(newWeights.begin(), newWeights.end());

			for (int i = 0; i < newWeights.size(); i++)
			{
				weights.push_back(newWeights[i]);
			}
		}

		void Train()
		{
			auto executionTime = 0.0;
			Display(false, true);
			std::vector<std::vector<double>> inputsFromFile = GetData(inputsFile);
			std::vector<std::vector<double>> targetsFromFile = GetData(targetsFile);

			if (inputsFromFile.size() != targetsFromFile.size())
			{
				printf("HiveMind() Error: Inputs and targets are different sizes\n");
				exit(EXIT_FAILURE);
			}
			printf("HiveMind() Training...\n");
			auto startTime = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < epoch; i++)
			{
				for (int j = 0; j < inputsFromFile.size(); j++)
				{
					SetInput(inputsFromFile[j]);
					SetTarget(targetsFromFile[j]);
					FeedForward();
					CalculateLoss();
					BackProp();
					if (displayLoss)
					{
						printf("\tEpoch: %d | Loss: %f\n", i, totalLoss);
					}
				}
			}
			auto stopTime = std::chrono::high_resolution_clock::now();
			executionTime = std::chrono::duration_cast<std::chrono::seconds>(stopTime - startTime).count();
			Display(false, true);
			printf("HiveMind() %d Training epochs performed in %f seconds\n", epoch, executionTime);
			SaveWeights();
		}

		void ProcessInformation()
		{
			auto executionTime = 0.0;
			std::vector<std::vector<double>> inputsFromFile = GetData(inputsFile);
			printf("HiveMind() Processing...\n\n");
			auto startTime = std::chrono::high_resolution_clock::now();
			for (int j = 0; j < inputsFromFile.size(); j++)
			{
				SetInput(inputsFromFile[j]);
				//SetConsoleTextAttribute(hConsole, 13);
				printf("Input %d: [ ", j);
				for (int k = 0; k < inputsFromFile[j].size(); k++)
				{
					printf("%f ", inputsFromFile[j][k]);
				}
				printf("]\n");
				//SetConsoleTextAttribute(hConsole, 0x7);
				FeedForward();
				Display(true, false);
			}
			auto stopTime = std::chrono::high_resolution_clock::now();
			executionTime = std::chrono::duration_cast<std::chrono::seconds>(stopTime - startTime).count();
			printf("HiveMind() Processed %d inputs in %f seconds\n\n", inputsFromFile.size(), executionTime);
		}

		Matrix Evaluate(std::vector<double> boardInput, bool trainNetwork, std::vector<double> gameResult)
		{
			SetInput(boardInput);
			FeedForward();

			if (trainNetwork)
			{
				SetTarget(gameResult);
				CalculateLoss();
				BackProp();
			}

			return layers[layers.size() - 1].ActivatedValuesToMatrix();
		}

		void Setup(std::string cfgPath)
		{
			LoadConfig(cfgPath);
			topologySize = topology.size();
			totalLoss = 0.0;

			//init layers
			for (int i = 0; i < topologySize; i++)
			{
				if (i > 0 && i < (topologySize - 1))
				{
					Layer l(topology[i], hiddenActFunction);
					layers.push_back(l);
				}
				else if (i == (topologySize - 1))
				{
					Layer l(topology[i], outputActFunction);
					layers.push_back(l);
				}
				else
				{
					Layer l(topology[i], F_SIGM);
					layers.push_back(l);
				}
			}

			// init weights
			for (int i = 0; i < topologySize - 1; i++)
			{
				Matrix m(topology[i], topology[i + 1], true);
				weights.push_back(m);
			}

			// init loss
			for (int i = 0; i < topology[topologySize - 1]; i++)
			{
				loss.push_back(0.0);
				derLoss.push_back(0.0);
			}

			LoadWeights();
		}

		HiveMind()
		{
			printf("Neural network Init()\n");
		}

		~HiveMind()
		{
		}
};