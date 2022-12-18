#pragma once

#include "Location.h"
#include "Board.h"
#include "Graphics.h"

class Snake
{
	class Segment
	{
	public:
		void InitHead(const Location& in_loc);
		void InitBody(Color c_in);
		void Follow(const Segment& next);
		void MoveBy(const Location& delta_loc);
		void Draw(Board& brd) const;
		const Location& GetLocation() const;		
	private:
		Location loc;
		Color c;
	};
public:
	Snake(Location& loc);
	void MoveBy(Location& delta_loc);
	Location GetTheHeadLocation(const Location& delta_loc) const;
	void Grow();
	void Draw(Board& brd);
	bool SnakeInItself(const Location& loc) const;
	bool SnakePos(const Location& loc) const;
private:
	static constexpr Color headColor = Colors::Yellow;
	static constexpr int nSegmentsMax = 100;
	Segment segments[nSegmentsMax];
	int nSegments = 1;
};