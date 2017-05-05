//    printf("philo_num %d\n",philo_num);
//    printf("mutex %d   state is :    %d\t\n", right,mutex[philo_num].__data.__lock );
//    printf("mutex %d   state is :    %d\t\n", left,mutex[philo_num].__data.__lock );
//    if (!mutex_locked(right(philo_num)) && !mutex_locked(left(philo_num)))
//    {
//        mutex_lock(right(philo_num));
//        mutex_lock(left(philo_num));
////        printf("inside 1");
////        printf("mutex %d   state is :    %d\t\n", right,mutex[philo_num].__data.__lock );
////        printf("mutex %d   state is :    %d\t\n", left,mutex[philo_num].__data.__lock );
//    }
//    else
//        if (!mutex_locked(right(philo_num)) && mutex_locked(left(philo_num)))
//        {
//            printf("inside 2");
//            mutex_lock(right(philo_num));
//            while(mutex_locked(left(philo_num)))
//            cond_wait_on(right(philo_num));
////            printf("mutex %d   state is :    %d\t\n", right,mutex[philo_num].__data.__lock );
////            printf("mutex %d   state is :    %d\t\n", left,mutex[philo_num].__data.__lock );
//        }
//
//        else
//            if (!mutex_locked(left(philo_num)) && mutex_locked(right(philo_num)))
//            {
//                printf("inside 3");
//                mutex_lock(left(philo_num));
//                while(mutex_locked(right(philo_num)))
//                {
//                    cond_wait_on(left(philo_num));
//                }
////                printf("mutex %d   state is :    %d\t\n", right,mutex[philo_num].__data.__lock );
////                printf("mutex %d   state is :    %d\t\n", left,mutex[philo_num].__data.__lock );
//            }




//    //printf("inside pickup forks with philosopher :%d \n", philo_num);
//    if (succ_trylock_on(right(philo_num)) && succ_trylock_on(left(philo_num)))
//    {
//        mutex_lock(right(philo_num));
//        mutex_lock(left(philo_num));
//    }
//    else
//        if(!succ_trylock_on(right(philo_num)) && !succ_trylock_on(left(philo_num)))
//        {
//            cond_wait_on(left(philo_num));
//            cond_wait_on(right(philo_num));
//        }
//        else
//            if (!succ_trylock_on(right(philo_num)) && succ_trylock_on(left(philo_num)))
//            {
//                mutex_lock(left(philo_num));
//                cond_wait_on(left(philo_num));
//            }
//            else
//            {
//                mutex_lock(right(philo_num));
//                cond_wait_on(right(philo_num));
//            }
//

