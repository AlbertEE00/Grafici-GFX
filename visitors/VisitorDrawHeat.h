#ifndef ARDU_DATAVIS_VISITOR_DRAW_HEAT_H
#define ARDU_DATAVIS_VISITOR_DRAW_HEAT_H

#include "../VisitorDraw.h"

class VisitorDrawHeat : public VisitorDraw
{
public:
	void visit(Data *data, ColorScheme *colors,Boundaries boundaries);
};


#endif //ARDU_DATAVIS_VISITOR_DRAW_HEAT_H