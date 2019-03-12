#include "../includes/lem-in.h"

int	runAllPath(t_list *pAllPath, t_graph **pGraph)
{
	int    size, bestSize = 0;
	float    minMoves;
	t_path *tmpLast;
	int    diffPath;
	float    best           = INT_MAX;

	size = 0;
	diffPath = 0;
	while (pAllPath)
	{
		size++;
		tmpLast = *(t_path **)pAllPath->content;
		minMoves = (float)((*pGraph)->totalAnts + diffPath + tmpLast->size - 1) / size;
		diffPath += (tmpLast->size - 1);
		pAllPath = pAllPath->next;
		if (minMoves < best)
		{
			bestSize = size;
			best = minMoves;
		}
		else
			break ;
	}
	printf("best - [%d]\n", bestSize);
	if (((int)best * 100) == (int)(best * 100.0))
		return ((int)best);
	else
		return ((int)best + 1);
}

void	fRunAnts(t_graph *pGraph, t_list pAllPath, int moves, int totalAnts)
{
	int currMove, i;
	int antPos[totalAnts];

	currMove = 0;
	ft_bzero(antPos, (size_t)totalAnts);
	while (currMove == moves && pGraph->array[pGraph->V - 1]->ants == totalAnts)
	{
		i = 0;
		while (i != totalAnts)
		{
			i++;
		}
	}
}
