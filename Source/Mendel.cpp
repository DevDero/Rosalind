
#include<iostream>
#include<vector>
using namespace std;
enum GeneType { recessive, dominant };

class Gene
{
public:
	GeneType allele1, allele2;
	Gene() = default;
	Gene(GeneType a1, GeneType a2) {
		allele1 = a1;
		allele2 = a2;
	}
};

class Individual {

public:
	Individual(Gene gene)
	{
		genotype = gene;
		Phenotype();
	}

	GeneType phenotype;
	Gene genotype;

	void Phenotype() {
		if (genotype.allele1 == recessive && genotype.allele2 == recessive) {
			phenotype = recessive;
		}
		else
			phenotype = dominant;

	}
};

struct Pair {
	Individual a;
	Individual b;
};
class MendelExperiment {
public:
	MendelExperiment(int _homodominantCount, int _heteroCount, int _homorecessiveCount) {
		homodominantCount = _homodominantCount;
		heteroCount = _heteroCount;
		homorecessiveCount = _homorecessiveCount;
		InitializePopulation();
	}
	void InitializePopulation() {
		CreatePopulation();
		CreatePairs();
		CreateOffSprings();
	}


private:
	int homodominantCount, heteroCount, homorecessiveCount;

	vector<Pair>Pairs;

	vector<Individual> Parents;
	vector<Individual> OffSpring;

	void CreatePopulation() {


		Gene homodominant(dominant, dominant);
		Gene homorecessive(recessive, recessive);
		Gene heterodominant(recessive, dominant);

		for (size_t i = 0; i < homodominantCount; i++)
		{
			Individual homodominantInd(homodominant);
			Parents.push_back(homodominantInd);
		}
		for (size_t i = 0; i < heteroCount; i++)
		{
			Individual heterodominantInd(heterodominant);
			Parents.push_back(heterodominantInd);
		}
		for (size_t i = 0; i < homorecessiveCount; i++)
		{
			Individual homorecessiveInd(homorecessive);
			Parents.push_back(homorecessiveInd);
		}
	}
	void CreatePairs() {
		for (size_t i = 0; i < Parents.size(); i++)
		{
			for (size_t j = i+1; j < Parents.size(); j++)
			{
				Pairs.push_back({ Parents.at(i), Parents.at(j) });
			}
		}
	}

	void CreateOffSprings() {
		int dominants=0;
		double ratio;

		for (auto &pair : Pairs) {
			Gene gene1(pair.a.genotype.allele1, pair.b.genotype.allele1);
			Gene gene2(pair.a.genotype.allele1, pair.b.genotype.allele2);
			Gene gene3(pair.a.genotype.allele2, pair.b.genotype.allele1);
			Gene gene4(pair.a.genotype.allele2, pair.b.genotype.allele2);

			Individual offspring1(gene1);
			Individual offspring2(gene2);
			Individual offspring3(gene3);
			Individual offspring4(gene4);

			if (offspring1.phenotype == dominant)
				dominants++;
			if (offspring2.phenotype == dominant)
				dominants++;
			if (offspring3.phenotype == dominant)
				dominants++;
			if (offspring4.phenotype == dominant)
				dominants++;

			OffSpring.push_back(offspring1);
			OffSpring.push_back(offspring2);
			OffSpring.push_back(offspring3);
			OffSpring.push_back(offspring4);

		}
		ratio = static_cast<double>(dominants) / (OffSpring.size());
	}
};