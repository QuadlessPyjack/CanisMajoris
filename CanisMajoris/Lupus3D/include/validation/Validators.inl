#ifndef IO_VALIDATORS_H
#define IO_VALIDATORS_H

static bool IOValidateIntRange(char* input, int min, int max, unsigned int size = 1)
{
	// input char is a signed value
	int minBound = -pow(127, size);
	int maxBound = pow(127, size);

	int inputNumber = 0;

	for (int i = 0; i < size; ++i)
	{
		inputNumber *= 10;
		inputNumber += *input;
		input++;
	}

	// check for overflows
	if (inputNumber < minBound)
	{
		return false;
	}

	// check for underflows
	if (inputNumber > maxBound)
	{
		return false;
	}

	if (inputNumber < min)
	{
		return false;
	}

	if (inputNumber > max)
	{
		return false;
	}

	return true;
}

static bool IOValidateInt(char* input, unsigned int size = 1)
{
	// input char is a signed value
	int minBound = -pow(127, size);
	int maxBound = pow(127, size);

	int inputNumber = 0;

	for (int i = 0; i < size; ++i)
	{
		inputNumber *= 10;
		inputNumber += *input;
		input++;
	}

	// check for overflows
	if (inputNumber < minBound)
	{
		return false;
	}

	// check for underflows
	if (inputNumber > maxBound)
	{
		return false;
	}

	return true;
}

static bool IOValidateInt(unsigned char* input, unsigned int size = 1)
{
	// input char is a signed value
	int minBound = 0;
	int maxBound = pow(255, size);

	int inputNumber = 0;

	for (int i = 0; i < size; ++i)
	{
		inputNumber *= 10;
		inputNumber += *input;
		input++;
	}

	// check for overflows
	if (inputNumber < minBound)
	{
		return false;
	}

	// check for underflows
	if (inputNumber > maxBound)
	{
		return false;
	}

	return true;
}

static bool IOValidateIntRange(unsigned char* input, int min, int max, unsigned int size = 1)
{
	// input char is a signed value
	int minBound = 0;
	int maxBound = pow(255, size);

	int inputNumber = 0;

	for (int i = 0; i < size; ++i)
	{
		inputNumber *= 10;
		inputNumber += *input;
		input++;
	}

	// check for overflows
	if (inputNumber < minBound)
	{
		return false;
	}

	// check for underflows
	if (inputNumber > maxBound)
	{
		return false;
	}

	if (inputNumber < min)
	{
		return false;
	}

	if (inputNumber > max)
	{
		return false;
	}

	return true;
}




#endif