// dito start sesend kay boss ron
//IF COMP
else if (printString[1] == 'o')
{
	if (printString[2] == 'm')
	{
		if (printString[3] == 'p' && printString[4] == '\0')
		{
			fprintf(wf, "Keywords: Comp\t\t%s\n", printString.c_str());
		}
	}
}

//IF default
if (printString[0] == 'd')
{
	if (printString[1] == 'e')
	{
		if (printString[2] == 'f')
		{
			if (printString[3] == 'a')
			{
				if (printString[4] == 'u')
				{
					if (printString[5] == 'l')
					{
						if (printString[6] == 't' && printString[7] == '\0')
						{
							fprintf(wf, "Keywords: default\t\t%s\n", printString.c_str());
						}
					}
				}
			}
		}
	}

	//IF do
	else if (printString[1] == 'o' && printString[2] == '\0')
	{
		fprintf(wf, "Keywords: do\t\t%s\n", printString.c_str());
	}
}

//IF else
if (printString[0] == 'e')
{
	if (printString[1] == 'l')
	{
		if (printString[2] == 's')
		{
			if (printString[3] == 'e' && printString[4] == '\0')
			{
				fprintf(wf, "Keywords: else\t\t%s\n", printString.c_str());
			}
		}
	}
	//IF euler
	else if (printString[1] == 'u')
	{
		if (printString[2] == 'l')
		{
			if (printString[3] == 'e')
			{
				if (printString[4] == 'r' && printString[5] == '\0')
				{
					fprintf(wf, "Reserved Words: euler\t\t%s\n", printString.c_str());
				}
			}
		}
	}
}

//IF false & for
if (printString[0] == 'f')
{
	if (printString[1] == 'a')
	{
		if (printString[2] == 'l')
		{
			if (printString[3] == 's')
			{
				if (printString[4] == 'e' && printString[5] == '\0')
				{
					fprintf(wf, "Reserved Words: false\t\t%s\n", printString.c_str());
				}
			}
		}
	}
	else if (printString[1] == 'o')
	{
		if (printString[2] == 'r' && printString[3] == '\0')
		{
			fprintf(wf, "Keyword: for\t\t%s\n", printString.c_str());
		}
	}
}

//IF Item
if (printString[0] == 'I')
{
	if (printString[1] == 't')
	{
		if (printString[2] == 'e')
		{
			if (printString[3] == 'm' && printString[4] == '\0')
			{
				fprintf(wf, "Keyword: Item\t\t%s\n", printString.c_str());
			}
		}
	}
}

//IF if   -- HOORAY! & int32

if (printString[0] == 'i')
{
	if (printString[1] == 'f' && printString[2] == '\0')
	{
		fprintf(wf, "Keyword: if\t\t%s\n", printString.c_str());
	}

	else if (printString[1] == 'n')
	{
		if (printString[2] == 't')
		{
			if (printString[3] == '3')
			{
				if (printString[4] == '2' && printString[5] == '\0')
				{
					fprintf(wf, "Reserved Word: int32\t\t%s\n", printString.c_str());
				}
			}
		}
	}
}

//IF Kelvin
if (printString[0] == 'k')
{
	if (printString[1] == 'e')
	{
		if (printString[2] == 'l')
		{
			if (printString[3] == 'v')
			{
				if (printString[4] == 'i')
				{
					if (printString[5] == 'n' && printString[6] == '\0')
					{
						fprintf(wf, "Reserved Word: kelvin\t\t%s\n", printString.c_str());
					}
				}
			}
		}
	}
}

//IF None & NOT & Number

if (printString[0] == 'N')
{
	if (printString[1] == 'o')
	{
		if (printString[2] == 'n')
		{
			if (printString[3] == 'e' && printString[4] == '\0')
			{
				fprintf(wf, "Reserved Word: None\t\t%s\n", printString.c_str());
			}
		}
	}
	//IF NOT
	else if (printString[1] == 'O')
	{
		if (printString[2] == 'T' && printString[3] == '\0')
		{
			fprintf(wf, "Keyword: NOT\t\t%s\n", printString.c_str());
		}
	}
	else if (printString[1] == 'u')
	{
		if (printString[2] == 'm')
		{
			if (printString[3] == 'b')
			{
				if (printString[4] == 'e')
				{
					if (printString[5] == 'r' && printString[6] == '\0')
					{
						fprintf(wf, "Keyword: Number\t\t%s\n", printString.c_str());
					}
				}
			}
		}
	}
}

//IF OR

if (printString[0] == 'O')
{
	if (printString[1] == 'R' && printString[2] == '\0')
	{
		fprintf(wf, "Keyword: OR\t\t%s\n", printString.c_str());
	}
}

//IF otherwise & odd
if (printString[0] == 'o')
{
	if (printString[1] == 't')
	{
		if (printString[2] == 'h')
		{
			if (printString[3] == 'e')
			{
				if (printString[4] == 'r')
				{
					if (printString[5] == 'w')
					{
						if (printString[6] == 'i')
						{
							if (printString[7] == 's')
							{
								if (printString[8] == 'e' && printString[9] == '\0')
								{
									fprintf(wf, "Keyword: otherwise\t\t%s\n", printString.c_str());
								}
							}
						}
					}
				}
			}
		}
	}
	else if (printString[1] == 'd')
	{
		if (printString[2] == 'd' && printString[3] == '\0')
		{
			fprintf(wf, "Reserved Word: odd\t\t%s\n", printString.c_str());
		}
	}
}

//IF pi

if (printString[0] == 'p')
{
	if (printString[1] == 'i' && printString[2] == '\0')
	{
		fprintf(wf, "Reserved Word: pi\t\t%s\n", printString.c_str());
	}
}

//IF resume & return

if (printString[0] == 'r')
{
	if (printString[1] == 'e')
	{
		if (printString[2] == 's')
		{
			if (printString[3] == 'u')
			{
				if (printString[4] == 'm')
				{
					if (printString[5] == 'e' && printString[6] == '\0')
					{
						fprintf(wf, "Reserved Word: resume\t\t%s\n", printString.c_str());
					}
				}
			}
		}
		else if (printString[2] == 't')
		{
			if (printString[3] == 'u')
			{
				if (printString[4] == 'r')
				{
					if (printString[5] == 'n' && printString[6] == '\0')
					{
						fprintf(wf, "Reserved Word: return\t\t%s\n", printString.c_str());
					}
				}
			}
		}
	}
}

//IF Sentence
if (printString[0] == 'S')
{
	if (printString[1] == 'e')
	{
		if (printString[2] == 'n')
		{
			if (printString[3] == 't')
			{
				if (printString[4] == 'e')
				{
					if (printString[5] == 'n')
					{
						if (printString[6] == 'c')
						{
							if (printString[7] == 'e' && printString[8] == '\0')
							{
								fprintf(wf, "Keyword: Sentence\t\t%s\n", printString.c_str());
							}
						}
					}
				}
			}
		}
	}
}

//IF stop & switch
if (printString[0] == 's')
{
	if (printString[1] == 't')
	{
		if (printString[2] == 'o')
		{
			if (printString[3] == 'p' && printString[5] == '\0')
			{
				fprintf(wf, "Reserved Word: stop\t\t%s\n", printString.c_str());
			}
		}
	}
	else if (printString[1] == 'w')
	{
		if (printString[2] == 'i')
		{
			if (printString[3] == 't')
			{
				if (printString[4] == 'c')
				{
					if (printString[5] == 'h' && printString[6] == '\0')
					{
						fprintf(wf, "Keyword: switch\t\t%s\n", printString.c_str());
					}
				}
			}
		}
	}
}

//IF then & true
if (printString[0] == 't')
{
	if (printString[1] == 'h')
	{
		if (printString[2] == 'e')
		{
			if (printString[3] == 'n' && printString[4] == '\0')
			{
				fprintf(wf, "Reserved Word: then\t\t%s\n", printString.c_str());
			}
		}
	}
	else if (printString[1] == 'r')
	{
		if (printString[2] == 'u')
		{
			if (printString[3] == 'e' && printString[4] == '\0')
			{
				fprintf(wf, "Reserved Word: true\t\t%s\n", printString.c_str());
			}
		}
	}
}

//IF Tralse
if (printString[0] == 'T')
{
	if (printString[1] == 'r')
	{
		if (printString[2] == 'a')
		{
			if (printString[3] == 'l')
			{
				if (printString[4] == 's')
				{
					if (printString[5] == 'e' && printString[6] == '\0')
					{
						fprintf(wf, "Keyword: Tralse\t\t%s\n", printString.c_str());
					}
				}
			}
		}
	}
}

//IF while
if (printString[0] == 'w')
{
	if (printString[1] == 'h')
	{
		if (printString[2] == 'i')
		{
			if (printString[3] == 'l')
			{
				if (printString[4] == 'e')
				{
					fprintf(wf, "Keyword: while\t\t%s\n", printString.c_str());
				}
			}
		}
	}
}
