#pragma once
#include "Match.h"
using namespace std;

size_t match::abMatch(size_t A, size_t B, size_t mask)
{
	size_t re = 0;
	re = (~((A | B) - (B << 1)) & A);//求取末位A
	re = re & mask;//过滤掉窗口外的结果
	return re;
}
vector<vector<size_t>> match::newbitMatchNomutily(query a, vector<vector<size_t>> bitSequence, unordered_map<string, int> eventmap, int timeContainer)
{
	long t1 = GetTickCount64();
	int twsize = a.timeWindow / timeContainer;
	int eventnum = eventmap[a.pt.evtype[a.pt.evtype.size() - 1]] - 1;
	vector<size_t> mask;
	for (int i = 0; i < bitSequence[eventnum].size(); i++)
	{
		size_t curmask = 0;
		size_t overmask = 0;
		size_t curfinalevent = bitSequence[eventnum][i];
		size_t curoverevent = 1;
		int overflag = 0;
		for (int j = 0; j < twsize - 1; j++)
		{
			if (overflag == 0)
			{
				curmask |= curfinalevent;
				curfinalevent = curfinalevent << 1;
			}
			else
			{
				overmask |= curoverevent;
				curoverevent = curoverevent << 1;
				curmask |= curfinalevent;
				curfinalevent = curfinalevent << 1;
			}
			if ((i != 0) && (curmask > 9223372036854775808))
			{
				overflag = 1;
			}
		}
		mask.push_back(curmask);
		if (overmask != 0)
		{
			mask[i - 1] |= overmask;
		}
	}

	int arryflag1 = 0;
	int negationflag = 0;
	int orflag = 0;
	vector<vector<size_t>> multilyResult;
	vector<size_t> timeWindow;

	size_t premask = 0;
	size_t prenum = 1;
	for (int i = 0; i < twsize - 1; i++)
	{
		premask |= prenum;
		prenum = prenum << 1;
	}

	int resultsize = bitSequence[0].size();


	for (int i = (a.pt.evtype.size() - 1); i >= 0; i--)
	{
		arryflag1 = eventmap[a.pt.evtype[i]] - 1;
		vector<size_t> oneResult;
		if (i == (a.pt.evtype.size() - 1))
		{
			oneResult = bitSequence[arryflag1];
		}
		else
		{

			if ((a.pt.sttype[i] == "normal") || (a.pt.sttype[i] == "kleeneClosure"))
			{
				if (negationflag != 0)
				{
					vector<size_t> negamask;
					negamask.push_back(0);
					for (int j = 0; j < resultsize; j++)
					{
						size_t curmask = 0;
						size_t overmask = 0;
						size_t curfinalevent = multilyResult[multilyResult.size() - 1][j];
						size_t curoverevent = 9223372036854775808;
						for (int j = 0; j < twsize - 1; j++)
						{
							if ((0 | curmask) == 0)
							{
								curmask |= curfinalevent;
								curfinalevent = curfinalevent >> 1;
							}
							else
							{
								overmask |= curoverevent;
								curoverevent = curoverevent >> 1;
								curmask |= curfinalevent;
								curfinalevent = curfinalevent >> 1;
							}
						}
						negamask.push_back(0);
						negamask[j] |= curmask;
						if (overmask != 0)
						{
							negamask[j + 1] |= overmask;
						}
					}
					for (int j = 0; j < resultsize; j++)
					{
						negamask[j] = negamask[j] & mask[j];
					}
					for (int j = 0; j < resultsize; j++)
					{
						if (j == 0)
						{
							oneResult.push_back(abMatch(bitSequence[arryflag1][j], multilyResult[multilyResult.size() - 2][j], negamask[j]));
						}
						else
						{
							oneResult.push_back((abMatch(bitSequence[arryflag1][j], multilyResult[multilyResult.size() - 2][j], negamask[j])));
						}
					}
					negationflag = 0;
				}
				else if (orflag != 0)
				{
					for (int j = 0; j < resultsize; j++)
					{
						oneResult.push_back(multilyResult[multilyResult.size() - 1][j]);
					}
					orflag = 0;
				}
				else
				{
					for (int j = 0; j < resultsize; j++)
					{
						if (j == 0)
						{
							oneResult.push_back(abMatch(bitSequence[arryflag1][j], multilyResult[multilyResult.size() - 1][j], mask[j]));
						}
						else
						{
							oneResult.push_back((abMatch(bitSequence[arryflag1][j], multilyResult[multilyResult.size() - 1][j], mask[j])));
						}
					}
				}
			}
			else if (a.pt.sttype[i] == "negation")
			{
				negationflag = 1;
				for (int j = 0; j < bitSequence[arryflag1].size(); j++)
				{
					if (j == 0)
					{
						oneResult.push_back(abMatch(bitSequence[arryflag1][j], multilyResult[multilyResult.size() - 1][j], mask[j]));
					}
					else
					{
						oneResult.push_back((abMatch(bitSequence[arryflag1][j], multilyResult[multilyResult.size() - 1][j], mask[j])));
					}

				}
			}
			else if (a.pt.sttype[i] == "or")
			{
				int arryflag2 = eventmap[a.pt.evtype[i - 1]] - 1;
				if (negationflag != 0)
				{
					vector<size_t> negamask;
					negamask.push_back(0);
					for (int j = 0; j < resultsize; j++)
					{
						vector<size_t> negamask;
						size_t nga = 0;
						size_t curmask = 0;
						size_t overmask = 0;
						size_t curfinalevent = multilyResult[multilyResult.size() - 1][j];
						size_t curoverevent = 9223372036854775808;
						for (int j = 0; j < twsize - 1; j++)
						{
							if ((0 | curmask) == 0)
							{
								curmask |= curfinalevent;
								curfinalevent = curfinalevent >> 1;
							}
							else
							{
								overmask |= curoverevent;
								curoverevent = curoverevent >> 1;
								curmask |= curfinalevent;
								curfinalevent = curfinalevent >> 1;
							}
						}
						negamask.push_back(0);
						negamask[j] |= curmask;
						if (overmask != 0)
						{
							negamask[j + 1] |= overmask;
						}
					}
					for (int j = 0; j < resultsize; j++)
					{
						negamask[j] = negamask[j] & mask[j];
					}
					for (int j = 0; j < resultsize; j++)
					{
						if (j == 0)
						{
							oneResult.push_back(abMatch((bitSequence[arryflag1][j] | bitSequence[arryflag2][j]), multilyResult[multilyResult.size() - 2][j], negamask[j]));
						}
						else
						{
							oneResult.push_back((abMatch((bitSequence[arryflag1][j] | bitSequence[arryflag2][j]), multilyResult[multilyResult.size() - 2][j], negamask[j])));
						}
					}
					negationflag = 0;
					orflag = 1;
				}
				else
				{
					for (int j = 0; j < resultsize; j++)
					{
						if (j == 0)
						{
							oneResult.push_back(abMatch((bitSequence[arryflag1][j] | bitSequence[arryflag2][j]), multilyResult[multilyResult.size() - 1][j], mask[j]));
						}
						else
						{
							oneResult.push_back((abMatch((bitSequence[arryflag1][j] | bitSequence[arryflag2][j]), multilyResult[multilyResult.size() - 1][j], mask[j])));

						}
					}
					orflag = 1;
				}
			}
		}
		multilyResult.push_back(oneResult);
	}
	long t2 = GetTickCount64();
	vector<size_t> Amask;
	vector<size_t> Bmask;
	size_t tempnum = 0;
	Amask.push_back(tempnum);
	Bmask.push_back(tempnum);
	for (int j = 0; j < resultsize; j++)
	{
		size_t curmaskA = 0;
		size_t overmaskA = 0;
		size_t curmaskB = 0;
		size_t overmaskB = 0;
		size_t curfinaleventA = multilyResult[multilyResult.size() - 1][j];
		size_t curfinaleventB = multilyResult[1][j];
		size_t curovereventA = 9223372036854775808;
		size_t curovereventB = 9223372036854775808;
		for (int i = 0; i < twsize; i++)
		{
			if ((curmaskA | 0) == 0)
			{
				curmaskA |= curfinaleventA;
				curfinaleventA = curfinaleventA >> 1;
			}
			else
			{
				overmaskA |= curovereventA;
				curovereventA = curovereventA >> 1;
				curmaskA |= curfinaleventA;
				curfinaleventA = curfinaleventA >> 1;
			}
			if ((curmaskB | 0) == 0)
			{
				curmaskB |= curfinaleventB;
				curfinaleventB = curfinaleventB >> 1;
			}
			else
			{
				overmaskB |= curovereventB;
				curovereventB = curovereventB >> 1;
				curmaskB |= curfinaleventB;
				curfinaleventB = curfinaleventB >> 1;
			}
		}
		Amask[j] |= curmaskA;
		Amask.push_back(tempnum);
		if (overmaskA != 0)
		{
			Amask[j + 1] |= overmaskA;
		}
		Bmask[j] |= curmaskB;
		Bmask.push_back(tempnum);
		if (overmaskB != 0)
		{
			Bmask[j + 1] |= overmaskB;
		}
	}
	for (int j = 0; j < resultsize; j++)
	{
		size_t temp = Amask[j] & Bmask[j];
		multilyResult[0][j] = multilyResult[0][j] & temp;
		for (int i = 1; i < multilyResult.size() - 2; i++)
		{
			multilyResult[i][j] = multilyResult[i][j] & Amask[j];
		}
	}
	long t3 = GetTickCount64();
	return multilyResult;
}
vector<vector<size_t>> match::newbitMatch(query a, vector<vector<size_t>> bitSequence, unordered_map<string, int> eventmap, int timeContainer)
{
	long t1 = GetTickCount64();
	int twsize = a.timeWindow / timeContainer;
	int eventnum = eventmap[a.pt.evtype[a.pt.evtype.size() - 1]] - 1;
	vector<size_t> mask;
	for (int i = 0; i < bitSequence[eventnum].size(); i++)
	{
		size_t curmask = 0;
		size_t overmask = 0;
		size_t curfinalevent = bitSequence[eventnum][i];
		size_t curoverevent = 1;
		int overflag = 0;
		for (int j = 0; j < twsize - 1; j++)
		{
			if (overflag == 0)
			{
				curmask |= curfinalevent;
				curfinalevent = curfinalevent << 1;
			}
			else
			{
				overmask |= curoverevent;
				curoverevent = curoverevent << 1;
				curmask |= curfinalevent;
				curfinalevent = curfinalevent << 1;
			}
			if ((i != 0) && (curmask > 9223372036854775808))
			{
				overflag = 1;
			}
		}
		mask.push_back(curmask);
		if (overmask != 0)
		{
			mask[i - 1] |= overmask;
		}
	}

	int arryflag1 = 0;
	int negationflag = 0;
	int orflag = 0;
	vector<vector<size_t>> multilyResult;
	vector<size_t> timeWindow;

	size_t premask = 0;
	size_t prenum = 1;
	for (int i = 0; i < twsize - 1; i++)
	{
		premask |= prenum;
		prenum = prenum << 1;
	}

	int resultsize = bitSequence[0].size();

	for (int i = (a.pt.evtype.size() - 1); i >= 0; i--)
	{
		arryflag1 = eventmap[a.pt.evtype[i]] - 1;
		vector<size_t> oneResult;
		if (i == (a.pt.evtype.size() - 1))
		{
			oneResult = bitSequence[arryflag1];
		}
		else
		{
			vector<size_t> findLack;
			size_t pre = 0, suf = 0;
			if ((a.pt.sttype[i] == "normal") || (a.pt.sttype[i] == "kleeneClosure"))
			{
				if (negationflag != 0)
				{
					vector<size_t> negamask;
					size_t nga = 0;
					negamask.push_back(nga);
					for (int j = 0; j < resultsize; j++)
					{
						size_t nga = 0;
						negamask.push_back(nga);
						size_t curmask = 0;
						size_t overmask = 0;
						size_t curfinalevent = multilyResult[multilyResult.size() - 1][j];
						size_t curoverevent = 9223372036854775808;
						for (int j = 0; j < twsize - 1; j++)
						{
							if ((0 | curmask) == 0)
							{
								curmask |= curfinalevent;
								curfinalevent = curfinalevent >> 1;
							}
							else
							{
								overmask |= curoverevent;
								curoverevent = curoverevent >> 1;
								curmask |= curfinalevent;
								curfinalevent = curfinalevent >> 1;
							}
						}
						negamask[j] |= curmask;
						if (overmask != 0)
						{
							negamask[j + 1] |= overmask;
						}
					}
					for (int j = 0; j < resultsize; j++)
					{
						negamask[j] = negamask[j] & mask[j];
					}
					for (int j = 0; j < resultsize; j++)
					{
						if (j == 0)
						{
							findLack.push_back(bitSequence[arryflag1][j] & premask);
							findLack.push_back(multilyResult[multilyResult.size() - 2][j] & premask);
							oneResult.push_back(abMatch(bitSequence[arryflag1][j], multilyResult[multilyResult.size() - 2][j], negamask[j]));
						}
						else
						{
							size_t temp1, temp2, temp3;
							temp1 = (findLack[0] << (twsize - 1)) | (bitSequence[arryflag1][j] >> (65 - twsize));
							temp2 = (findLack[1] << (twsize - 1)) | (multilyResult[multilyResult.size() - 2][j] >> (65 - twsize));
							temp3 = ((negamask[j - 1] & premask) << (twsize - 1)) | (negamask[j] >> (65 - twsize));
							size_t findResult = abMatch(temp1, temp2, temp3);

							pre = findResult >> (twsize - 1);
							suf = findResult << (65 - twsize);

							oneResult[j - 1] = oneResult[j - 1] | pre;
							oneResult.push_back(suf | (abMatch(bitSequence[arryflag1][j], multilyResult[multilyResult.size() - 2][j], negamask[j])));

							findLack[0] = bitSequence[arryflag1][j] & premask;
							findLack[1] = multilyResult[multilyResult.size() - 2][j] & premask;
						}
					}
					negationflag = 0;
				}
				else if (orflag != 0)
				{
					for (int j = 0; j < resultsize; j++)
					{
						oneResult.push_back(multilyResult[multilyResult.size() - 1][j]);
					}
					orflag = 0;
				}
				else
				{
					for (int j = 0; j < resultsize; j++)
					{
						if (j == 0)
						{
							findLack.push_back(bitSequence[arryflag1][j] & premask);
							findLack.push_back(multilyResult[multilyResult.size() - 1][j] & premask);
							oneResult.push_back(abMatch(bitSequence[arryflag1][j], multilyResult[multilyResult.size() - 1][j], mask[j]));
						}
						else
						{
							size_t temp1, temp2, temp3;
							temp1 = (findLack[0] << (twsize - 1)) | (bitSequence[arryflag1][j] >> 65 - (twsize));
							temp2 = (findLack[1] << (twsize - 1)) | (multilyResult[multilyResult.size() - 1][j] >> 65 - (twsize));
							temp3 = ((mask[j - 1] & premask) << (twsize - 1)) | (mask[j] >> (65 - twsize));
							size_t findResult = abMatch(temp1, temp2, temp3);

							pre = findResult >> (twsize - 1);
							suf = findResult << (65 - twsize);

							oneResult[j - 1] = oneResult[j - 1] | pre;
							oneResult.push_back(suf | (abMatch(bitSequence[arryflag1][j], multilyResult[multilyResult.size() - 1][j], mask[j])));

							findLack[0] = bitSequence[arryflag1][j] & premask;
							findLack[1] = multilyResult[multilyResult.size() - 1][j] & premask;
						}
					}
				}
			}
			else if (a.pt.sttype[i] == "negation")
			{
				negationflag = 1;
				for (int j = 0; j < bitSequence[arryflag1].size(); j++)
				{
					if (j == 0)
					{
						findLack.push_back(bitSequence[arryflag1][j] & premask);
						findLack.push_back(multilyResult[multilyResult.size() - 1][j] & premask);
						oneResult.push_back(abMatch(bitSequence[arryflag1][j], multilyResult[multilyResult.size() - 1][j], mask[j]));
					}
					else
					{
						size_t temp1, temp2, temp3;
						temp1 = (findLack[0] << (twsize - 1)) | (bitSequence[arryflag1][j] >> 65 - (twsize));
						temp2 = (findLack[1] << (twsize - 1)) | (multilyResult[multilyResult.size() - 1][j] >> 65 - (twsize));
						temp3 = ((mask[j - 1] & premask) << (twsize - 1)) | (mask[j] >> (65 - twsize));
						size_t findResult = abMatch(temp1, temp2, temp3);

						pre = findResult >> (twsize - 1);
						suf = findResult << (65 - twsize);

						oneResult[j - 1] = oneResult[j - 1] | pre;
						oneResult.push_back(suf | (abMatch(bitSequence[arryflag1][j], multilyResult[multilyResult.size() - 1][j], mask[j])));

						findLack[0] = bitSequence[arryflag1][j] & premask;
						findLack[1] = multilyResult[multilyResult.size() - 1][j] & premask;
					}

				}

			}
			else if (a.pt.sttype[i] == "or")
			{
				int arryflag2 = eventmap[a.pt.evtype[i - 1]] - 1;
				if (negationflag != 0)
				{
					vector<size_t> negamask;
					negamask.push_back(0);
					for (int j = 0; j < resultsize; j++)
					{
						size_t curmask = 0;
						size_t overmask = 0;
						size_t curfinalevent = multilyResult[multilyResult.size() - 1][j];
						size_t curoverevent = 9223372036854775808;
						for (int j = 0; j < twsize - 1; j++)
						{
							if ((0 | curmask) == 0)
							{
								curmask |= curfinalevent;
								curfinalevent = curfinalevent >> 1;
							}
							else
							{
								overmask |= curoverevent;
								curoverevent = curoverevent >> 1;
								curmask |= curfinalevent;
								curfinalevent = curfinalevent >> 1;
							}
						}
						negamask.push_back(0);
						negamask[j] |= curmask;
						if (overmask != 0)
						{
							negamask[j + 1] |= overmask;
						}
					}
					for (int j = 0; j < resultsize; j++)
					{
						negamask[j] = negamask[j] & mask[j];
					}
					for (int j = 0; j < resultsize; j++)
					{
						if (j == 0)
						{
							findLack.push_back((bitSequence[arryflag1][j] | bitSequence[arryflag2][j]) & premask);
							findLack.push_back(multilyResult[multilyResult.size() - 2][j] & premask);
							oneResult.push_back(abMatch((bitSequence[arryflag1][j] | bitSequence[arryflag2][j]), multilyResult[multilyResult.size() - 2][j], negamask[j]));
						}
						else
						{
							size_t temp1, temp2, temp3;
							temp1 = (findLack[0] << (twsize - 1)) | ((bitSequence[arryflag1][j] | bitSequence[arryflag2][j]) >> (65 - twsize));
							temp2 = (findLack[1] << (twsize - 1)) | (multilyResult[multilyResult.size() - 2][j] >> (65 - twsize));
							temp3 = ((negamask[j - 1] & premask) << (twsize - 1)) | (negamask[j] >> (65 - twsize));
							size_t findResult = abMatch(temp1, temp2, temp3);

							pre = findResult >> (twsize - 1);
							suf = (findResult << (65 - twsize));

							oneResult[j - 1] = oneResult[j - 1] | pre;
							oneResult.push_back(suf | (abMatch((bitSequence[arryflag1][j] | bitSequence[arryflag2][j]), multilyResult[multilyResult.size() - 2][j], negamask[j])));

							findLack[0] = (bitSequence[arryflag1][j] | bitSequence[arryflag2][j]) & premask;
							findLack[1] = multilyResult[multilyResult.size() - 2][j] & premask;
						}
					}
					negationflag = 0;
					orflag = 1;
				}
				else
				{
					for (int j = 0; j < resultsize; j++)
					{
						if (j == 0)
						{
							findLack.push_back((bitSequence[arryflag1][j] | bitSequence[arryflag2][j]) & premask);
							findLack.push_back(multilyResult[multilyResult.size() - 1 - negationflag][j] & premask);
							oneResult.push_back(abMatch((bitSequence[arryflag1][j] | bitSequence[arryflag2][j]), multilyResult[multilyResult.size() - 1][j], mask[j]));
						}
						else
						{
							size_t temp1, temp2, temp3;
							temp1 = (findLack[0] << (twsize - 1)) | ((bitSequence[arryflag1][j] | bitSequence[arryflag2][j]) >> (65 - twsize));
							temp2 = (findLack[1] << (twsize - 1)) | (multilyResult[multilyResult.size() - 1][j] >> (65 - twsize));
							temp3 = ((mask[j - 1] & premask) << (twsize - 1)) | (mask[j] >> (65 - twsize));
							size_t findResult = abMatch(temp1, temp2, temp3);

							pre = findResult >> (twsize - 1);
							suf = (findResult << (65 - twsize));

							oneResult[j - 1] = oneResult[j - 1] | pre;
							oneResult.push_back(suf | (abMatch((bitSequence[arryflag1][j] | bitSequence[arryflag2][j]), multilyResult[multilyResult.size() - 1][j], mask[j])));

							findLack[0] = (bitSequence[arryflag1][j] | bitSequence[arryflag2][j]) & premask;
							findLack[1] = multilyResult[multilyResult.size() - 1 - negationflag][j] & premask;
						}
					}
					orflag = 1;
				}
			}
		}
		multilyResult.push_back(oneResult);
	}
	long t2 = GetTickCount64();
	vector<size_t> Amask;
	vector<size_t> Bmask;
	size_t tempnum = 0;
	Amask.push_back(tempnum);
	Bmask.push_back(tempnum);
	for (int j = 0; j < resultsize; j++)
	{
		size_t curmaskA = 0;
		size_t overmaskA = 0;
		size_t curmaskB = 0;
		size_t overmaskB = 0;
		size_t curfinaleventA = multilyResult[multilyResult.size() - 1][j];
		size_t curfinaleventB = multilyResult[1][j];
		size_t curovereventA = 9223372036854775808;
		size_t curovereventB = 9223372036854775808;
		for (int i = 0; i < twsize; i++)
		{
			if ((curmaskA | 0) == 0)
			{
				curmaskA |= curfinaleventA;
				curfinaleventA = curfinaleventA >> 1;
			}
			else
			{
				overmaskA |= curovereventA;
				curovereventA = curovereventA >> 1;
				curmaskA |= curfinaleventA;
				curfinaleventA = curfinaleventA >> 1;
			}
			if ((curmaskB | 0) == 0)
			{
				curmaskB |= curfinaleventB;
				curfinaleventB = curfinaleventB >> 1;
			}
			else
			{
				overmaskB |= curovereventB;
				curovereventB = curovereventB >> 1;
				curmaskB |= curfinaleventB;
				curfinaleventB = curfinaleventB >> 1;
			}
		}
		Amask[j] |= curmaskA;
		Amask.push_back(tempnum);
		if (overmaskA != 0)
		{
			Amask[j + 1] |= overmaskA;
		}
		Bmask[j] |= curmaskB;
		Bmask.push_back(tempnum);
		if (overmaskB != 0)
		{
			Bmask[j + 1] |= overmaskB;
		}
	}
	for (int j = 0; j < resultsize; j++)
	{
		size_t temp = Amask[j] & Bmask[j];
		multilyResult[0][j] = multilyResult[0][j] & temp;
		for (int i = 1; i < multilyResult.size() - 2; i++)
		{
			multilyResult[i][j] = multilyResult[i][j] & Amask[j];
		}
	}
	long t3 = GetTickCount64();
	return multilyResult;
}