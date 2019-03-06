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
	int 	size, minMoves;
	t_path	*tmpLast, *tmpCurrent, *tmpBest;
//	int		*antsForPath;
	int diffPath;
	int best = INT_MAX;

	size = 1;
	tmpBest = *(t_path **)pAllPath->content;
	minMoves = (*pGraph)->totalAnts + tmpBest->size - 1;
	if (!(pAllPath = pAllPath->next))
	{
		return ;
	}
	tmpCurrent = *(t_path **)pAllPath->next->content;
	diffPath = tmpCurrent->size - 1 ;
//	ft_printf("minmoves === %d\n", minMoves);
	while (pAllPath->next)// && diffPath <= (*pGraph)->totalAnts)
	{
		size++;
		tmpLast = *(t_path **)pAllPath->content;
		tmpCurrent = *(t_path **)pAllPath->next->content;
		minMoves = ((*pGraph)->totalAnts + diffPath + tmpCurrent->size) / size;
		diffPath += tmpCurrent->size - 1;
//		ft_printf("minmoves === %d\n", minMoves);
		pAllPath = pAllPath->next;
		if (minMoves < best)
			best = minMoves;
		else
			;
	}
	ft_printf("\n\n<<{cyan}%d{eoc}>>\n\n", best);
//	ft_printf("minmoves === %d\n", minMoves);
//	antsForPath = malloc(size * sizeof(int));
//	antsForPath[0] = (*pGraph)->totalAnts;
	
//	addPath();

}
