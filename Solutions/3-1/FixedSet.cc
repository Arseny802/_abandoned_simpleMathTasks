#include "FixedSet.h"

FixedSet::FixedSet()
{
    this->mersenne_twister_ = std::mt19937(time(0));
}

bool FixedSet::IsPrimeNumber(const int number) 
{
    unsigned int iter;
    
    for (iter = 2; iter * iter <= number; ++iter)
    {
        if (number % iter == 0) 
        {
            return false;
        }
    }
    return true;
}

int FixedSet::GetNextPrimeNumber(const int number) 
{
    unsigned int iter = number + 1;
    for( ; !this->IsPrimeNumber(iter); ++iter);
    return iter;
}

int FixedSet::GetHashFromKey(const int key) const
{
    if (this->hash_function_coefficient_p_ == 0 || this->fixed_set_size_ == 0)
    {
        return 0;
    }
    return std::abs((hash_function_coefficient_a_ * key + 
        hash_function_coefficient_b_) % hash_function_coefficient_p_) 
        % this->fixed_set_size_;
}

int FixedSet::GetHashFromRowAndKey(HashTableRow row, int key) const
{
    if (this->hash_function_coefficient_p_ == 0 || row.table_length == 0)
    {
        return 0;
    }
    return std::abs((row.coefficient_a * key + row.coefficient_b) 
        % hash_function_coefficient_p_) % row.table_length;
}

void FixedSet::InitializeHashTableRows(std::vector<int> numbers) 
{
    unsigned int iter, sub_iter;
    unsigned int row, column;
    bool collision_found;
    std::vector<int> items_to_write, items_hashes;
    
    for (iter = 0; iter < this->fixed_set_size_; ++iter) 
    {
        this->fixed_set_[iter].table_length = 0;
    }
        
    for (iter = 0; iter < this->fixed_set_size_; ++iter)
    {
        ++this->fixed_set_[this->GetHashFromKey(numbers[iter])].table_length;
    }
    
    for (iter = 0; iter < this->fixed_set_size_; ++iter) 
    {
        if (this->fixed_set_[iter].table_length) 
        {
            this->fixed_set_[iter].table_length *= 
                this->fixed_set_[iter].table_length;
            this->fixed_set_[iter].values.resize
                (this->fixed_set_[iter].table_length);
            
            if (this->fixed_set_[iter].table_length == 1) 
            {
                this->fixed_set_[iter].coefficient_a = 0;
                this->fixed_set_[iter].coefficient_b = 0;
                for (sub_iter = 0; sub_iter < this->fixed_set_size_; ++sub_iter)
                {
                    if (iter == this->GetHashFromKey(numbers[sub_iter]))
                    {
                        this->fixed_set_[iter].values[0] = numbers[sub_iter];
                    }
                }
            }
            else
            {
                for (sub_iter = 0; sub_iter < this->fixed_set_size_; ++sub_iter)
                {
                    if (iter == this->GetHashFromKey(numbers[sub_iter]))
                    {
                        items_to_write.push_back(numbers[sub_iter]);
                    }
                }
                do
                {
                    collision_found = false;
                    std::uniform_int_distribution<> randomize_a
                        (1, this->hash_function_coefficient_p_);
                    std::uniform_int_distribution<> randomize_b
                        (0, this->hash_function_coefficient_p_);
                    this->fixed_set_[iter].coefficient_a = 
                        randomize_a(mersenne_twister_);
                    this->fixed_set_[iter].coefficient_b = 
                        randomize_b(mersenne_twister_);
                    
                    for (auto &tmp_item : items_to_write)
                    {
                        row = this->GetHashFromRowAndKey
                            (this->fixed_set_[iter], tmp_item);
                        
                        for (auto &created_item_hash : items_hashes)
                        {
                            if (created_item_hash == row)
                            {
                                collision_found = true;
                                break;
                            }
                        }
                        if (collision_found)
                        {
                            break;
                        }
                        items_hashes.push_back(row);
                    }
                    items_hashes.clear();
                } while (collision_found);
                
                for (auto &tmp_item : items_to_write)
                {
                    row = this->GetHashFromRowAndKey
                        (this->fixed_set_[iter], tmp_item);
                    this->fixed_set_[iter].values[row] = tmp_item;
                }
                items_to_write.clear();
            }
        }
    }
}

void FixedSet::Initialize(const std::vector<int>& numbers)
{
    this->fixed_set_size_ = numbers.size();
    this->fixed_set_.resize(this->fixed_set_size_);
    
    this->hash_function_coefficient_p_ = 
        this->GetNextPrimeNumber(kMaxInputInteger);
    if (this->fixed_set_size_ > 1)
    {
        std::uniform_int_distribution<> randomize_a
            (1, this->hash_function_coefficient_p_);
        std::uniform_int_distribution<> randomize_b
            (0, this->hash_function_coefficient_p_); 
        
        this->hash_function_coefficient_a_ = randomize_a(mersenne_twister_);
        this->hash_function_coefficient_b_ = randomize_b(mersenne_twister_);
    }
    else
    {
        this->hash_function_coefficient_a_ = 1;
        this->hash_function_coefficient_b_ = 0;
    }
    
    this->InitializeHashTableRows(numbers);
}

bool FixedSet::Contains(int number) const
{
    unsigned int column, row;
    
    column = this->GetHashFromKey(number);
    if (this->fixed_set_size_ == 0 || this->fixed_set_size_ < column)
    {
        return false;
    }
    
    row = this->GetHashFromRowAndKey(fixed_set_[column], number);
    if (fixed_set_[column].table_length == 0 || 
        fixed_set_[column].table_length < row)
    {
        return false;
    }
    return fixed_set_[column].values[row] == number;
}