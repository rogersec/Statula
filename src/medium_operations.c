#include "medium_operations.h"

int central_moment(struct dataset *set,int degree)
{
	assert(set->number_count > 0);
	double c_moment = 0;

	for(int i = 0;i < set->number_count;i++){
		c_moment += pow((set->numbers[i]-set->mean),degree);
	}
	c_moment /= set->number_count;
	if(degree == 2)
		set->central_moment = c_moment;	
	else if(degree == 4)
		set->kurtosis = c_moment;
	return degree > 1 ? 1 : 0;
}

int standard_deviation(struct dataset *set)
{
	assert(set->number_count > 0);
	set->standard_deviation = sqrt(set->central_moment);
	return 1;
}

int mean_absolute_deviation(struct dataset *set)
{
	double m_o_d = 0;

	for(int i=0;i < set->number_count;i++){
		m_o_d += fabs(set->numbers[i] - set->mean);
	}
	set->mean_absolute_deviation = m_o_d / set->number_count;
	return 1;
}

int coefficient_of_variation(struct dataset *set)
{
	if(set->mean ==0){
		set->coefficient_of_variation = 0;
		return -1;
	}
	set->coefficient_of_variation = (set->standard_deviation / set->mean) * 100;
	return 1;
}

int kurtosis(struct dataset *set)
{
	central_moment(set,4);
	if(set->standard_deviation == 0)
		return 0;
	else
		set->kurtosis = set->kurtosis / pow(set->standard_deviation,4) - 3;
	return 1;
}

int skewness(struct dataset *set)
{
	if(set->standard_deviation == 0)
		return 0;
	set->skewness = 3 * ((set->mean - (set->median)) / (set->standard_deviation));
	return set->skewness <= 1 && set->skewness >= -1 ? 1 : 0;
}
