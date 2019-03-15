#include "../includes/lem-in.h"

void	onePath(t_path *currWay, t_graph *pGraph, int antOnStart)
{
	int mover;

	mover = currWay->size;
	while (mover--)
	{
		if (mover && pGraph->array[currWay->path[mover - 1]]->ants > -1)
		{
			if (mover != currWay->size - 1)
			{
				pGraph->array[currWay->path[mover]]->ants = pGraph->array[currWay->path[mover - 1]]->ants;
			}
			else if (mover == currWay->size - 1)
			{
				pGraph->array[currWay->path[mover]]->ants++;
			}
			ft_printf("L%d->%s ", pGraph->array[currWay->path[mover - 1]]->ants, pGraph->array[currWay->path[mover]]->name);
			pGraph->array[currWay->path[mover - 1]]->ants = -1;
		}
	}
	if (antOnStart)
	{
		pGraph->array[currWay->path[0]]->ants = pGraph->totalAnts - pGraph->array[0]->ants;
		ft_printf("L%d->%s ", pGraph->array[currWay->path[0]]->ants, pGraph->array[currWay->path[0]]->name);
		pGraph->array[0]->ants--;
	}
}

int	countIteration(t_list *pAllPath, t_graph **pGraph, int *size)
{
	float    minMoves;
	t_path *tmpLast;
	int    diffPath;
	float    best;

	best = INT_MAX;
	diffPath = 0;
	while (pAllPath)
	{
		(*size)++;
		tmpLast = *(t_path **)pAllPath->content;
		minMoves = (float)((*pGraph)->totalAnts + diffPath + tmpLast->size - 1) / *size;
		diffPath += (tmpLast->size - 1);
		pAllPath = pAllPath->next;
		if (minMoves < best)
			best = minMoves;
		else
			break ;
	}
	return ((int)best * 100) == (int)(best * 100.0) ? (int)best : (int)best + 1;
}

void	runAllPath(t_list *pAllPath, t_graph **pGraph)
{
	int i, j = 0, nPath = 0;
	t_list	*crawler;
	gresult = countIteration(pAllPath, pGraph, &nPath);
	while ((*pGraph)->array[(*pGraph)->V - 1]->ants != (*pGraph)->totalAnts && j++ < 51)
	{
		i = 0;
		crawler = pAllPath;
		while(i < nPath)
		{
			onePath(*(t_path **)(crawler->content), *pGraph, (*pGraph)->array[0]->ants);
			crawler = crawler->next;
			i++;
		}
		ft_printf("\t[%d]\n", (*pGraph)->array[0]->ants);
	}
}

//void	fRunAnts(t_graph *pGraph, t_list pAllPath, int moves, int totalAnts)
//{
//	int currMove, i;
//	int antPos[totalAnts];
//
//	currMove = 0;
//	ft_bzero(antPos, (size_t)totalAnts);
//	while (currMove == moves && pGraph->array[pGraph->V - 1]->ants == totalAnts)
//	{
//		i = 0;
//		while (i != totalAnts)
//		{
//
//			i++;
//		}
//	}
//}
