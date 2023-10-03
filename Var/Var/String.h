#pragma once
class String
{
private:
	char* str;
	static size_t CountStr;
public:
	String();
	String(size_t size);
	String(const char* str);
	String(const String& OtherString);
	~String();

	void SetStr(char* str);
	char* GetStr();

	static size_t GetCountStr();

	void EnterStr();
	void Show() const;

	String& operator=(const String& OtherString) noexcept;
	String operator*(const String& OtherString) noexcept;
};

