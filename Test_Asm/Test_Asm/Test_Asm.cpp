int main()
{
	int a = 1;
	
	__asm
	{
		mov eax, a
		add eax, 2
		mov a, eax
	}
}
