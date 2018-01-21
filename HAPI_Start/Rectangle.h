#pragma once
class Rectangle
{
public:
	int left{ 0 }, right{ 0 }, top{ 0 }, bottom{ 0 };

	Rectangle() = default;
	Rectangle(int l, int r, int t, int b) : left(l), right(r), top(t), bottom(b) {}
	Rectangle(int w, int h) : left(0), right(w), top(0), bottom(h) {}

	void ClipTo(const Rectangle &other);
	bool CompletelyContains(const Rectangle &other) const;
	bool CompletelyOutside(const Rectangle &other) const;
	void Translate(int dx, int dy);

	void ReduceRectangleSize(int amount);

	int Width() const { return right - left; }
	int Height() const { return bottom - top; }
};

