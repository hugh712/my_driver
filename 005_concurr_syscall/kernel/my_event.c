
struct CustomEvent{
	int eventNum;
	wait_queue_head_t *p;
	struct CustomEvent *next;
}

CustomEvent * lpevent_head = NULL;
CustomEvent * lpevent_end = NULL;

CustomEvent * FindEventNum(int eventNum, CustomEvent **prev)
{
	CustomEvent *tmp=lpevent_head;
	*prev=NULL;

	while(tmp)
	{
		if(tmp->eventNum==eventNum)
			return tmp;

		*prev=tmp;
		tmp=tmp->next;
	}
	return NULL;
}

asmlinkage int sys_CustomEvent_open(int eventNum)
{
	CustomEvent *new;
	CustomEvent *prev;

	if(eventNum)
	{
		if(!FindEventNum(eventNum, &prev))
			return -1;
		else
			return eventNum;
	}
	else
	{
		new =(CustomEvent *)kmalloc(sizeof(CustomEvent), GFP_KERNEL);
		new->p = (wait_queue_head_t *)kmalloc(sizeof(wait_queue_head_t), GFP_KERNEL);
		new->next=NULL;
		new->p->task_list.next = &new->p->task_list;
		new->p->task_list.prev = &new->p->task_list;

		if(!lpevent_head)
		{
			new->eventNum = 2;
			lpevent_head = lpevent_end = new;
			return new->eventNum;
		}
		else
		{
			new->eventNum = lpevent_end->eventNum + 2;
			lpevent_end->next = new;
			lpevent_end = new;
		}
		return new->eventNum;
	}
return 0;
}

asmlinkage int sys_CustomEvent_wait(int eventNum)
{
	CustomEvent *tmp;
	CustomEvent *prev=NULL;

	if((tmp = FindEventNum(eventNum, &prev))!=NUL)
	{
		DEFINE_WAIT(wait);
		prepare_to_wait(tmp->p, &wait, TASK_INTERRUPTIBLE);

		schedule();
		finish_wait(tmp->p, &wait);
	return eventNum;	
	}
	return -1;

}

asmlinkage int sys_CustomEvent_signal(int eventNum)
{
	CustomEvent *tmp = NULL;
	CustomEvent *prev = NULL;

	if(!(tmp=FindEventNum(eventNum, &prev)))
		return 0;

	wake_up(tmp->p);
	return 1;
}

asmlinkage int sys_CustomEvent_close(int eventNum)
{
	CustomEvent *prev = NULL;
	CustomEvent *releaseItem;

	if(releaseItem = FindEventNum(eventNum, &prev))
	{
		if(releaseItem == lpevent_end)
			lpevent_end=prev;
		else if(releaseItem==lpevent_head)
			lpevent_head=lpevent_head->next;
		else
			prev->next=releaseItem->next;

		if(releaseItem)
			kfree(releaseItem);
		return releaseItem;
	}
	return 0;

}

