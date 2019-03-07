#include "../includes/lem-in.h"

int		countAllPath(t_list *pList);

int		countAllPath(t_list *pList)
{
	int counter;

	counter = 0;
	while (pList)
	{
		counter++;
		pList = pList->next;
	}
	return (counter);
}

void	runAllPath(t_list *pAllPath, t_graph **pGraph)
{
	int    size, bestSize = 0;
	float    minMoves;
	t_path *tmpLast;
//	int		*antsForPath;
	int    diffPath;
	float    best           = INT_MAX;

	size = 0;
	diffPath = 0;
//	tmpBest = *(t_path **)pAllPath->content;
//	minMoves = (*pGraph)->totalAnts + tmpBest->size - 1;
//	diffPath = tmpBest->size - 1;
//	ft_printf("minmoves === %.2f  dif[%d] size - >%d<\n", minMoves, diffPath, tmpBest->size);
	while (pAllPath)
	{
		size++;
		tmpLast = *(t_path **)pAllPath->content;
		minMoves = (float)((*pGraph)->totalAnts + diffPath + tmpLast->size - 1) / size;
		diffPath += (tmpLast->size - 1);
//		ft_printf("minmoves === %.2f  dif[%d] size - >%d<\n", minMoves, diffPath, tmpLast->size);
		pAllPath = pAllPath->next;
		if (minMoves < best)
		{
			bestSize = size;
			best = minMoves;
		}
		else
			break ;
	}
//	ft_printf("\n<< %.2f [%d]>>\n", best, bestSize);/**/
	if (((int)best * 10) == (int)(best * 10.0))
		gresult = (int)best;
	else
		gresult = (int)best + 1;
//	ft_printf("minmoves === %d\n", minMoves);
//	antsForPath = malloc(size * sizeof(int));
//	antsForPath[0] = (*pGraph)->totalAnts;
//	addPath();
}
