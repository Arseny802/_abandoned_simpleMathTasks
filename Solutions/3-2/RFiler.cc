#include "RFiler.h"

RFiler::RFiler() { }

RFiler::RFiler(std::string file_name)
{
    this->current_file_name_ = file_name;
    this->current_file_stream_.open(file_name.c_str());
}

bool RFiler::Open(std::string file_name)
{
    this->current_file_name_ = file_name;
    this->current_file_stream_.open(file_name.c_str());
    return this->IsFileOpened();
}

void RFiler::Close()
{
    if (this->IsFileOpened())
    {
        this->current_file_stream_.close();
    }
}

void RFiler::Read()
{
    std::string line;

    if (this->current_file_stream_.is_open())
    {
        while (getline(this->current_file_stream_, line))
        {
            std::cout << line << '\n';
        }
        this->current_file_stream_.close();
    }
    else
    {
        std::cout << "File for reading \""
            << this->current_file_name_ << "\" is closed!\n";
    }
}

void RFiler::PrintLastString()
{
    std::string line;

    if (this->current_file_stream_.is_open())
    {
        while (getline(this->current_file_stream_, line))
        {
            //do nothing, just getting last string
        }
        std::cout << line << '\n';
        this->current_file_stream_.close();
    }
    else
    {
        std::cout << "File for reading \""
            << this->current_file_name_ << "\" is closed!\n";
    }
}

bool RFiler::IsFileOpened()
{
    return this->current_file_stream_.is_open();
}

unsigned int RFiler::ReadNumber()
{
    std::string line;
    unsigned int result = 0;

    if (this->current_file_stream_.is_open())
    {
        if (getline(this->current_file_stream_, line))
        {
            result = atoi(line.c_str());
        }
        else
        {
            std::cout << "Error occurred while file \""
                << this->current_file_name_ << "\" reading - no lines!\n";
        }
        ++this->current_line_number_;
    }
    else
    {
        std::cout << "File for reading \""
            << this->current_file_name_ << "\" is closed!\n";
    }

    return result;
}

std::vector<int> RFiler::ReadNumbers(unsigned int count)
{
    std::string line, token;
    std::stringstream string_stream;
    std::vector<int> result(count);

    if (this->current_file_stream_.is_open())
    {
        if (getline(this->current_file_stream_, line))
        {
            string_stream.str(line);
            for (unsigned int iter = 0; iter < count; ++iter)
            {
                std::getline(string_stream, token, kDelimeter);
                result[iter] = atoi(token.c_str());
            }
        }
        else
        {
            std::cout << "Error occurred while file \""
                << this->current_file_name_ << "\" reading - no lines!\n";
        }
        ++this->current_line_number_;
    }
    else
    {
        std::cout << "File for reading \""
            << this->current_file_name_ << "\" is closed!\n";
    }

    return result;
}

bool RFiler::SetLineNumber(unsigned int new_line_number)
{
    if (new_line_number > this->current_line_number_)
    {
        return this->IncreaseLineNumber(new_line_number - 
            this->current_line_number_);
    }
    else if (new_line_number < this->current_line_number_)
    {
        return this->IncreaseLineNumber(this->current_line_number_ - 
            new_line_number);
    }
    return true;
}

bool RFiler::IncreaseLineNumber(unsigned int number_for)
{
    std::string line;
    for (unsigned int iter = 0; iter < number_for; ++iter)
    {
        if (!getline(this->current_file_stream_, line))
        {
            return false;
        }
        ++this->current_line_number_;
    }
    return true;
}

bool RFiler::DecreaseLineNumber(unsigned int number_for)
{
    std::string line;
    unsigned int new_position = current_line_number_ - number_for;

    if (new_position < 0)
    {
        return false;
    }
    this->current_file_stream_.seekg(0, this->current_file_stream_.beg);

    for (unsigned int iter = 0; iter < new_position; ++iter)
    {
        if (!getline(this->current_file_stream_, line))
        {
            return false;
        }
        ++this->current_line_number_;
    }
    return true;
}

RFiler::~RFiler()
{
    if (this->IsFileOpened())
    {
        this->current_file_stream_.close();
    }
}