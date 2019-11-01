#include "FixedSet.h"

FixedSet::FixedSet()
{
    this->mersenne_twister_ = std::mt19937(time(0));
}

bool FixedSet::IsPrimeNumber(const int number) 
{
    for(int iter = 2; iter * iter <= number; ++iter)
    {
        if(number % iter == 0) 
        {
            return false;
        }
    }
    return true;
}

int FixedSet::GetNextPrimeNumber(const int number) 
{
    int iter = number + 1;
    for( ; !this->IsPrimeNumber(iter); ++iter);
    return iter;
}

int FixedSet::get_hash_function(const int key) const
{
    return ((hash_function_coefficient_a_ * key + hash_function_coefficient_b_)
        % hash_function_coefficient_p_) % this->fixed_set_size_;
}

int FixedSet::get_row_hash_func(hash_table_level_2 H, int key) const
{
    return ((H.a * key) % H.p) % H.m;
}

void FixedSet::make_hash_raw(std::vector<int> numbers) 
{
    unsigned int iter;
    
    for (iter = 0; iter < this->fixed_set_size_; ++iter) 
    {
        this->fixed_set_[iter].m = 0;
    }
        
    for (iter = 0; iter < this->fixed_set_size_; ++iter)
    {
        ++this->fixed_set_[this->get_hash_function(numbers[iter])].m;
    }
    
    for (iter = 0; iter < this->fixed_set_size_; ++iter) 
    {
        if (this->fixed_set_[iter].m) 
        {
            this->fixed_set_[iter].m *= this->fixed_set_[iter].m;
            
            if (this->fixed_set_[iter].m == 1) 
            {
                this->fixed_set_[iter].a = 0;
                this->fixed_set_[iter].b = 0;
                this->fixed_set_[iter].p = this->hash_function_coefficient_p_;
            }
            else
            {
                this->fixed_set_[iter].b = (rand() %  this->fixed_set_[iter].m);
                this->fixed_set_[iter].a = (rand() % (this->fixed_set_[iter].m - 1)) + 1;
                this->fixed_set_[iter].p = this->hash_function_coefficient_p_;
            }
        }
    }
    this->AddElements(numbers);
}

void FixedSet::AddElements(std::vector<int> numbers) 
{
    unsigned int iter;
    int row, column;
    
    for (iter = 0; iter < numbers.size(); ++iter) 
    {
        column = this->get_hash_function(numbers[iter]);
        row = this->get_row_hash_func(this->fixed_set_[column], numbers[iter]);
        this->fixed_set_[column].value = numbers[iter];
    }
}

void FixedSet::Initialize(const std::vector<int>& numbers)
{
    this->fixed_set_size_ = numbers.size();
    this->fixed_set_.resize(this->fixed_set_size_);
    
    std::uniform_int_distribution<> random_int_for_a(1, this->fixed_set_size_ - 1);
    std::uniform_int_distribution<> random_int_for_b(0, this->fixed_set_size_); 
    
    this->hash_function_coefficient_p_ = this->GetNextPrimeNumber(kMaxInputInteger);
    this->hash_function_coefficient_a_ = random_int_for_a(mersenne_twister_);
    this->hash_function_coefficient_b_ = random_int_for_b(mersenne_twister_);
    
    this->make_hash_raw(numbers);
    this->AddElements(numbers);
}

bool FixedSet::Contains(int number) const
{
    unsigned int column, row;
    
    column = this->get_hash_function(number);
    if (fixed_set_.size() < column)
    {
        return false;
    }
    
    row = this->get_row_hash_func(fixed_set_[column], number);
    return fixed_set_[column].value == number;
}