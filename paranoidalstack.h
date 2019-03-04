#include <assert.h>
#include <stdlib.h>

typedef int stackType;
const stackType CANARY = 0xF;
const stackType POISON = 0x0;
class Stack
{
private:
	int checksum;
	int calcChecksum();
	unsigned int capacity_;
	unsigned int size_;
	stackType* data_;

public:
	unsigned int getSize();
	unsigned int getCapacity();
	int push(stackType value);
	stackType pop();
	int checkOk();
	Stack();
	~Stack();
};


int Stack::checkOk()
{
	if (this->data_[0] != CANARY)
		return 1;
	if (this->data_[this->capacity_ + 1] != CANARY)
		return 2;
	if (this->size_ > this->capacity_)
		return 3;
	if (this->checksum != this->calcChecksum())
		return 4;
	return 0;
}

unsigned int Stack::getSize()
{
	assert("Stack check failed" && !this->checkOk());
	
	return this->size_;
}

unsigned int Stack::getCapacity()
{
	assert("Stack check failed" && !this->checkOk());
	
	return this->capacity_;
}

int Stack::push(stackType value)
{
	assert("Stack check failed" && !this->checkOk());
	
	if (this->capacity_ == this->size_ + 2)
	{
		this->capacity_ *= 2;
		this->data_ = (stackType*)realloc(this->data_, sizeof(stackType) * this->capacity_+ 1);
		this->data_[this->capacity_ + 1] = CANARY;
	}

	this->size_++;
	this->data_[this->size_] = value;
	this->checksum = this->calcChecksum();
	assert("Stack check failed" && !this->checkOk());

	return 1;
}

stackType Stack::pop()
{
	assert("Stack check failed" && !this->checkOk());

	if (this->capacity_ > this->size_ * 3)
	{
		this->capacity_ /= 2;
		this->data_ = (stackType*)realloc(this->data_, sizeof(stackType) * this->capacity_);
		this->data_[this->capacity_ + 1] = CANARY;
	}
	
	this->size_--;
	this->checksum = this->calcChecksum();

	return(this->data_[this->size_ + 1]);
}

int Stack::calcChecksum()
{
	int checksum = this->size_^this->capacity_^this->data_[this->size_]^this->data_[1];
	return checksum;
}

Stack::Stack()
{
	this->capacity_ = 16;
	this->size_ = 0;
	this->data_ = (stackType*)calloc(17, sizeof(stackType));
	this->data_[0] = CANARY;
	this->data_[capacity_ + 1] = CANARY;

	for (int i = 1; i <= capacity_; i++)
		this->data_[i] = POISON;

	this->checksum = this->calcChecksum();
	assert("Stack check failed" && !this->checkOk());
}

Stack::~Stack()
{
	assert("Stack check failed" && !this->checkOk());
	for (int i = 0; i < this->capacity_ + 1; i++)
		this->data_[i] = POISON;
	
	this->size_ = -1;
	this->capacity_ = -1;
	this->checksum = -1;


}