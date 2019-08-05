#ifndef GRAFICI_GFX_VISITOR_DRAW_AXIS_H
#define GRAFICI_GFX_VISITOR_DRAW_AXIS_H

#include "../Data.h"
#include "../Display.h"

void axisPlot(DisplayDriver *displayDriver, DataSet *dataset, Boundaries *boundaries, ColorScheme *colorScheme)
{
	//vertical lines
	for (int itX = 0; itX <= 10; itX++)
	{
		DataPoint a(itX / 10.0, 0.0);
		DataPoint b(itX / 10.0, 1.0);
		displayDriver->drawLine(boundaries->project(a).setColor(colorScheme->line) /* .fadeColor(0.8, _colorScheme->bkgColor)*/,
								boundaries->project(b).setColor(colorScheme->line) /* .fadeColor(0.8, _colorScheme->bkgColor)*/);

		//horrizontal sub line
		for (int itY = 0; itY <= 10; itY++)
		{
			if (itX < 10)
			{
				DataPoint a(itX / 10.0, itY / 10.0);
				DataPoint b((itX + 1.0) / 10.0, itY / 10.0);
				displayDriver->drawLine(boundaries->project(a).setColor(colorScheme->line) /* .fadeColor(0.8, _colorScheme->bkgColor)*/,
										boundaries->project(b).setColor(colorScheme->line) /* .fadeColor(0.8, _colorScheme->bkgColor)*/);
			}
		}
	}
}

#endif //GRAFICI_GFX_VISITOR_DRAW_AXIS_H