#ifndef IMENU_H
#define IMENU_H

class IMenu
{
public:
	virtual ~IMenu() noexcept = default;
	virtual void show() const = 0;
};

#endif // !IMENU_H

