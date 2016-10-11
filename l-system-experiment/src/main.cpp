#include <iostream>
#include "./lsystem/RewriteEngine.h"
#include "./lsystem/language/Token.h"
#include "./lsystem/production/Production.h"
#include "./lsystem/production/SimpleProduction.h"

class AlphaToken : public lsystem::Token
{
	private:
		char value;

	public:
		AlphaToken(char _t) : value(_t) {};
		operator char() const { return value; };
};

void printList(lsystem::tList output)
{
	for (auto it = output.begin(); it != output.end(); it++) { std::cout << (char) (*it); }
	std::cout << std::endl;
}

int main()
{
	lsystem::RewriteEngine engine = lsystem::RewriteEngine();

	auto p1 = lsystem::SimpleProduction(AlphaToken('A'), std::vector<AlphaToken>({ AlphaToken('D'), AlphaToken('A'), AlphaToken('D') }));
	engine.addProduction(p1);

	lsystem::tList input = lsystem::tList({ AlphaToken('B'), AlphaToken('C'), AlphaToken('A') });

	std::cout << "Input: ";
	printList(input);

	auto output = engine.rewrite(5, input.begin(), input.end());

	std::cout << "Output: ";
	printList(output);

	system("PAUSE");

	return 0;
}