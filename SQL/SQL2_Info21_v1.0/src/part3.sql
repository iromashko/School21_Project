-- 1) Написать функцию, возвращающую таблицу TransferredPoints в более человекочитаемом виде

drop function if exists fnc_transferred_points();
create or replace function fnc_transferred_points()
returns table(Peer1 varchar, Peer2 varchar, PointsAmount bigint) as
    $$
    begin
        return query (select t1.checkingpeer, t1.checkedpeer, (t1.pointsamount - t1.pointsamount) as PointsAmount
                        from transferredpoints as t1);
    end;
    $$ language plpgsql;

-- select * from fnc_transferred_points();

-- 2) Написать функцию, которая возвращает таблицу вида: ник пользователя, название проверенного задания, кол-во полученного XP

drop function if exists fnc_peer_success_project();
create or replace function fnc_peer_success_project()
    returns table(Peer varchar, Task varchar, XP integer) as
    $$
    begin
        return query (select c.peer, c.task, x.xpamount
                  from checks c
                      inner join xp x on c.id = x."Check"
                      inner join p2p p on c.id = p."Check"
                  where p.state = 'Success');
    end;
    $$ language plpgsql;

-- select * from fnc_peer_success_project();

-- 3) Написать функцию, определяющую пиров, которые не выходили из кампуса в течение всего дня

drop function if exists fnc_not_left_peer();
create or replace function fnc_not_left_peer(in day date)
    returns setof varchar as
    $$
    begin
        return query ((select peer from timetracking
                                  where state = 1
                                  and "Date" = day)
        except (select peer from timetracking
                            where state = 2
                            and "Date" = day));
    end;
    $$ language plpgsql;

-- select * from fnc_not_left_peer('2020-01-02');

-- 4) Найти процент успешных и неуспешных проверок за всё время
drop procedure if exists pcd_success_projects_percent;
create or replace procedure pcd_success_projects_percent(out SuccessfulChecks real,
                                                        out UnsuccessfulChecks real) as
    $$
    begin
        create view full_table as ( select p2p.state as p2p_state, verter.state as verter_state
                                  from checks
                                           join p2p on checks.id = p2p."Check"
                                           left join verter on checks.id = verter."Check"
                                  where p2p.state in ('Success', 'Failure') and
                                      (verter.state in ('Success', 'Failure') or verter.state is null ));
        select round((((select count(*) from full_table
                        where p2p_state = 'Success' and (verter_state = 'Success' or verter_state is null)) * 100) /
                      (select count(*) from full_table)::real)) into SuccessfulChecks;
        select round((((select count(*) from full_table
                        where p2p_state = 'Failure' or verter_state = 'Failure') * 100) /
                      (select count(*) from full_table)::real)) into UnsuccessfulChecks;
        drop view full_table cascade ;
    end;
    $$ language plpgsql;

-- call pcd_success_projects_percent(null, null);

-- 5) Посчитать изменение в количестве пир поинтов каждого пира по таблице TransferredPoints
drop procedure if exists pcd_peer_points_changes;
create or replace procedure pcd_peer_points_changes(in ref refcursor) as
    $$
    begin
        open ref for
            with amount_received as (select checkingpeer as Peer,
                                            sum(pointsamount) as PointsChange
                                     from transferredpoints
                                     group by checkingpeer
                                     order by checkingpeer),
                 amount_spent as (select checkedpeer as Peer,
                                         sum(pointsamount) as PointsChange
                                  from transferredpoints
                                  group by checkedpeer
                                  order by checkedpeer)
            select ar.Peer, ar.PointsChange - "as".PointsChange as PointsChange
            from amount_received ar
                     inner join amount_spent "as" on ar.Peer = "as".Peer;
    end;
    $$ language plpgsql;

-- begin;
-- call pcd_peer_points_changes('cursor_name');
-- fetch all in "cursor_name";
-- end;

-- 6) Посчитать изменение в количестве пир поинтов каждого пира по таблице, возвращаемой первой функцией из Part 3
drop procedure if exists pcd_peer_points_changes_2 cascade;
create or replace procedure pcd_peer_points_changes_2(in ref refcursor) as
    $$
    begin
        open ref for
            with p1 as (select Peer1 as peer, cast (sum(PointsAmount) as integer) as PointsChange
                        from fnc_transferred_points()
                        group by Peer1),
                 p2 as (select Peer2 as peer, cast (sum(PointsAmount) as integer) as PointsChange
                        from fnc_transferred_points()
                        group by Peer2)
            select coalesce(p1.peer, p2.peer) as peer, (coalesce(p1.PointsChange, 0) - coalesce(p2.PointsChange, 0)) as pointschange
            from p1
                     full join p2 on p1.peer = p2.peer
            order by PointsChange desc ;
    end ;
    $$ language plpgsql;

-- begin ;
-- call pcd_peer_points_changes_2('ref');
-- fetch all in "ref";
-- end ;

-- 7) Определить самое часто проверяемое задание за каждый день
drop procedure if exists pcd_most_reviewed_task cascade;
create or replace procedure pcd_most_reviewed_task(in ref refcursor) as
    $$
    begin
        open ref for
            with t1 as (select task, date, COUNT(*) as counts
                        from checks
                        group by task, date),
                 t2 as (select t1.task, t1.date, rank() over (partition by t1.date order by t1.counts) as rank
                        from t1)
            select t2.date, t2.task
            from t2
            where rank = 1;
    end ;
    $$ language plpgsql;

-- begin;
-- call pcd_most_reviewed_task('ref');
-- fetch all in"ref";
-- end;

-- 8) Определить длительность последней P2P проверки
drop procedure if exists pcd_last_check_duration cascade ;
create or replace procedure pcd_last_check_duration(in ref refcursor) as
    $$
    begin
        open ref for
            with last_check as (select "Check" as check_id
                                from p2p
                                where id = (select max(id)
                                            from p2p
                                            where state = 'Start'))
            select (max(time) - min(time))::time as times
            from last_check lc
                     inner join p2p on lc.check_id = p2p."Check";
    end;
    $$ language plpgsql;

-- begin;
-- call pcd_last_check_duration('cursor_name');
-- fetch all in "cursor_name";
-- end;

-- 9) Найти всех пиров, выполнивших весь заданный блок задач и дату завершения последнего задания
drop procedure if exists pcd_completed_block cascade;
create or replace procedure pcd_completed_block(in block varchar, in ref refcursor) as
    $$
    begin
        open ref for
            with tasks_block as (select * from tasks
                                 where title similar to concat(block, '[0-9]%')),
                 last_task as (select max(title) as title from tasks_block),
                 date_of_successful_check as (select checks.peer, checks.task, checks.date
                                              from checks
                                                       join p2p on checks.id = p2p."Check"
                                              where p2p.state = 'Success'
                                              group by checks.id)
            select date_of_successful_check.peer as Peer, date_of_successful_check.date
            from date_of_successful_check
                     join last_task on date_of_successful_check.task = last_task.title;
    end;
    $$ language plpgsql;

-- begin ;
-- call pcd_completed_block('D%', 'ref');
-- fetch all in"ref";
-- end;

-- 10) Определить, к какому пиру стоит идти на проверку каждому обучающемуся
drop procedure if exists pcd_recommendation_list cascade;
create or replace procedure pcd_recommendation_list(in ref refcursor) as
    $$
    begin
        open ref for
            with list_of_recommendation as (select peer1, recommendedpeer, count(peer) as count
                                            from friends f
                                                     inner join recommendations r on f.peer2 = r.peer
                                            where peer1 <> r.recommendedpeer
                                            group by peer1, recommendedpeer
                                            order by 1, count desc, 2),
                 table_of_max_count_recommendation as (select peer1, max(count) as max_count
                                                       from list_of_recommendation
                                                       group by peer1)

            select mcr.peer1 as Peer, recommendedpeer as RecommendedPeer
            from table_of_max_count_recommendation mcr
                     inner join list_of_recommendation lor on lor.count = mcr.max_count and
                                                              lor.peer1 = mcr.peer1
            order by Peer;
    end;
    $$ language plpgsql;

-- begin;
-- call pcd_recommendation_list('cursor_name');
-- fetch all in "cursor_name";
-- end;

-- 11) Определить процент пиров, которые:
-- - Приступили только к блоку 1
-- - Приступили только к блоку 2
-- - Приступили к обоим
-- - Не приступили ни к одному
drop procedure if exists pcd_peers_block_started_percent cascade;
create or replace procedure pcd_peers_block_started_percent(in ref refcursor, block_name_1 varchar, block_name_2 varchar) as
    $$
    begin
        open ref for
            with first_block as (select distinct peer from checks
                                 where task like block_name_1),
                 second_block as (select distinct peer from checks
                                  where task like block_name_2),
                 both_blocks as (select distinct peer from first_block
                                 intersect
                                 select distinct peer from second_block),
                 didnt_start as (select nickname as peer from peers
                                 except
                                 (select distinct peer from first_block
                                  union
                                  select distinct peer from second_block))
            select (select count(peer) from first_block) * 100 / count(nickname)  as StartedBlock1,
                   (select count(peer) from second_block) * 100 / count(nickname) as StartedBlock2,
                   (select count(peer) from both_blocks) * 100 / count(nickname)  as StartedBothBlocks,
                   (select count(peer) from didnt_start) * 100 / count(nickname)  as DidntStartAnyBlock
            from peers;
    end;
    $$ language plpgsql;

-- begin;
-- call pcd_peers_block_started_percent('cursor_name', 'D%', 'D%');
-- fetch all in "cursor_name";
-- end;

-- 12) Определить N пиров с наибольшим числом друзей
drop procedure if exists pcd_most_friends_peer cascade;
create or replace procedure pcd_most_friends_peer(in limits int, in ref refcursor) as
    $$
    begin
        open ref for
            with find_friends as (select nickname,
                                         (case when nickname = f.peer1 then peer2 else peer1 end) as friends
                                            from peers
                                            join friends f on peers.nickname = f.peer1 or peers.nickname = f.peer2)
            select nickname, count( friends ) as FriendsCount
            from find_friends
            group by nickname
            order by FriendsCount desc
            limit limits;

    end;
    $$ language plpgsql;

-- begin ;
-- call pcd_most_friends_peer(2, 'ref');
-- fetch all in "ref";
-- end;

-- 13) Определить процент пиров, которые когда-либо успешно проходили проверку в свой день рождения
drop procedure if exists pcd_success_reviews_on_birthday cascade;
create or replace procedure pcd_success_reviews_on_birthday(in ref refcursor) as
    $$
    begin
        open ref for
            with succ_and_fail_stat as (select count(peer)
                filter (where p2p.state = 'Success' and v.state <> 'Failure') as success,
                                            count(peer) filter (where (p2p.state = 'Success' and v.state = 'Failure') or
                                                                      (p2p.state = 'Failure')) as fail
                                        from checks c
                                        inner join verter v on c.id = v."Check"
                                        inner join p2p on c.id = p2p."Check"
                                        inner join peers p on p.nickname = c.peer
                                        where extract(month from c.date) = extract(month from p.birthday)
                                          and extract(day from c.date) = extract(day from p.birthday))
            select round(100 * success /(success + fail)) as SuccessfulChecks,
                   round(100 * fail / (success + fail))   as UnsuccessfulChecks
            from succ_and_fail_stat;
    end;
    $$ language plpgsql;

-- begin;
-- call pcd_success_reviews_on_birthday('cursor_name');
-- fetch all in "cursor_name";
-- end;

-- 14) Определить кол-во XP, полученное в сумме каждым пиром
drop procedure if exists pcd_total_xp cascade;
create or replace procedure pcd_total_xp(in ref refcursor) as
    $$
    begin
        open ref for
        with max_xp as (select c.peer, max(x.xpamount) as max_xp
                        from checks c
                        join xp x on c.id = x."Check"
                        group by c.peer, task)
        select m.peer as Peer, sum( max_xp ) as xp
        from max_xp m
        group by m.peer
        order by xp desc ;
    end;
    $$ language plpgsql;

-- begin;
-- call pcd_total_xp('cursor_name');
-- fetch all in "cursor_name";
-- end;

-- 15) Определить всех пиров, которые сдали заданные задания 1 и 2, но не сдали задание 3
drop procedure if exists pcd_completed_task cascade;
create or replace procedure pcd_completed_task(in ref refcursor, in first_task text, in second_task text,
                                               in third_task text) as
    $$
    begin
        open ref for
            with success as (select "Check", Peer as CheckedPeer, Task
                             from p2p
                                 inner join checks c on c.id = p2p."Check"
                             where state = 'Success'
                             except all
                             (select "Check", Peer as CheckedPeer, Task
                              from verter
                                  inner join checks c on c.id = verter."Check"
                              where state = 'Failure'
                              union all
                              select "Check", Peer as CheckedPeer, Task
                              from p2p
                                  inner join checks c on c.id = p2p."Check"
                              where state = 'Failure'))
            select distinct s1.CheckedPeer from success s1
                full join success s2 on s2.CheckedPeer = s1.CheckedPeer
                full join success s3 on s3.CheckedPeer = s1.CheckedPeer
                                           where s1.task = first_task
                                             and s2.task = second_task
                                             and s3.task <> third_task;
        end;
$$ language plpgsql;

-- begin;
-- call pcd_completed_task('cursor_name', 'SQL1_Bootcamp', 'SQL2_Info21 v1.0', 'SQL3_RetailAnalitycs v1.0');
-- fetch all in "cursor_name";
-- end;

-- 16) Используя рекурсивное обобщенное табличное выражение, для каждой задачи вывести кол-во предшествующих ей задач
create or replace function fnc_count(in pre_tasks text) returns integer as
    $$
    with recursive count_tasks as (select title, parenttask, 0 as count
                                   from tasks
                                   where title = pre_tasks
                                   union
                                   select tasks.title, tasks.parenttask, count_tasks.count + 1
                                   from tasks
                                       join count_tasks on tasks.title = count_tasks.parenttask)

    select max(count) from count_tasks
    $$ language sql;
drop procedure if exists pcd_pre_task cascade;
create or replace procedure pcd_pre_task(in ref refcursor) as
    $$
    begin
        open ref for
            select tasks.title as task, fnc_count(tasks.title) as PrevCount
            from tasks
            order by PrevCount;
    end;
    $$ language plpgsql;

-- begin;
-- call pcd_pre_task('cursor_name');
-- fetch all in "cursor_name";
-- end;

-- 17) Найти "удачные" для проверок дни. День считается "удачным", если в нем есть хотя бы N идущих подряд успешных проверки
drop procedure if exists pcd_lucky_day cascade;
create or replace procedure pcd_lucky_day(in n int, in ref refcursor) as
    $$
    begin
        open ref for with t as ( select * from checks
                                 join p2p p on checks.id = p."Check"
                                 left join verter v on checks.id = v."Check"
                                 join tasks t2 on checks.task = t2.title
                                 join xp x on checks.id = x."Check"
                                 where p.state = 'Success' and v.state = 'Success')
        select date from t
        where t.xpamount >= t.maxxp * 0.8
        group by date
        having count( date ) >= n;
    end;
    $$ language plpgsql;

-- begin;
-- call pcd_lucky_day(1, 'ref');
-- fetch all in "ref";
-- end;

-- 18) Определить пира с наибольшим числом выполненных заданий
drop procedure if exists pcd_peer_max_done cascade;
create or replace procedure pcd_peer_max_done(in ref refcursor) as
    $$
    begin
        open ref for
            select peer, count(task) as completed
            from checks
            group by peer
            order by 2 desc
            limit 1;
    end;
    $$ language plpgsql;

-- begin;
-- call pcd_peer_max_done('cursor_name');
-- fetch all in "cursor_name";
-- end;

-- 19) Определить пира с наибольшим количеством XP
drop procedure if exists pcd_peer_max_xp cascade;
create or replace procedure pcd_peer_max_xp(in ref refcursor) as
    $$
    begin
        open ref for
        select c.peer, sum(xpamount) as xp
        from xp
        join checks c on c.id = xp."Check"
        group by c.peer
        order by xp desc
        limit 1;
    end;
    $$ language plpgsql;

-- begin;
-- call pcd_peer_max_xp('cursor_name');
-- fetch all in "cursor_name";
-- end;

-- 20) Определить пира, который провел сегодня в кампусе больше всего времени
drop procedure if exists pcd_max_time_in_campus cascade;
create or replace procedure pcd_max_time_in_campus(in ref refcursor) as
    $$
    begin
        open ref for
            with t1 as (select id, peer, "Time" from timetracking
                                                where state = 1 and "Date" = now()::date),
                 t2 as (select id, peer, "Time" from timetracking
                                                where state = 2 and "Date" = now()::date),
                 t12 as (select distinct on (t1.id)
                             t1.id as id_1, t1.peer as peer_1, t1."Time" as time_1,
                             t2.id as id_2, t2.peer as peer_2, t2."Time" as time_2
                         from t1
                             inner join t2 on t1.peer = t2.peer and t1."Time" < t2."Time")

            select peer_1 as peer
            from t12
            group by 1
            having (sum(time_2 - time_1)::time) = (select (sum(time_2 - time_1)::time) as t3
                                                   from t12
                                                   group by peer_1
                                                   order by 1 desc
                                                   limit 1);
    end;
    $$ language plpgsql;

-- begin;
-- call pcd_max_time_in_campus('cursor_name');
-- fetch all in "cursor_name";
-- end;

-- 21) Определить пиров, приходивших раньше заданного времени не менее N раз за всё время
drop procedure if exists pcd_coming_early cascade;
create or replace procedure pcd_coming_early(in "check_time" time, in n int, in ref refcursor) as
    $$
    begin
        open ref for
        select peer
        from (select peer, min("Time") as min_time
              from timetracking
              where state = 1
              group by "Date", peer) as t
        where min_time < "check_time"
        group by peer
        having count(peer) >= N;
    end;
    $$ language plpgsql;

-- begin;
-- call pcd_coming_early('23:00:00', 1,'cursor_name');
-- fetch all in "cursor_name";
-- end;

-- 22) Определить пиров, выходивших за последние N дней из кампуса больше M раз
drop procedure if exists pcd_out_of_campus cascade;
create or replace procedure pcd_out_of_campus(in ref refcursor, in n int, in m int) as
    $$
    begin
        open ref for
        select peer
        from (select peer, "Date", (count(*) - 1) as counts
              from timetracking
              where state = 2 and "Date" > (current_date - n)
              group by peer, "Date") as t
        group by peer
        having sum(counts) > m;
    end;
    $$ language plpgsql;

-- begin;
-- call pcd_out_of_campus('cursor_name', 10000, 0);
-- fetch all in "cursor_name";
-- end;

-- 23) Определить пира, который пришел сегодня последним
drop procedure if exists pcd_last_visited_peer cascade;
create or replace procedure pcd_last_visited_peer(in ref refcursor) as
    $$
    begin
        open ref for
            select peer
            from timetracking
            where state = 1
              and "Date" = current_date
            order by "Time" desc
            limit 1;
    end;
    $$ language plpgsql;

-- begin;
-- call pcd_last_visited_peer('cursor_name');
-- fetch all in "cursor_name";
-- end;

-- 24) Определить пиров, которые выходили вчера из кампуса больше чем на N минут
drop procedure if exists pcd_time_out_of_campus cascade;
create or replace procedure pcd_time_out_of_campus(in ref refcursor, in N int) as
    $$
    begin
        open ref for
        with find_first_input as (select peer, "Date", min("Time") as min_t
                                  from timetracking
                                  where state = 1 and "Date" = (current_date - 1)
                                  group by peer, "Date"),
             last as (select peer, "Date", MAX("Time") as max_t
                      from timetracking
                      where state = 2 and "Date" = (current_date - 1)
                      group by peer, "Date"),
             ins as (select t.peer as peer, t."Time" as time
                     from timetracking as t
                         join find_first_input as ff on t.peer = ff.peer
                                and t."Time" != ff.min_t and t.state = 1
                     where t."Date" = (current_date - 1)),
             outs as (select t.peer as peer, t."Time" as time
                      from timetracking as t
                          join last as fl on t.peer = fl.peer
                                and t."Time" != fl.max_t and t.state = 2
                      where t."Date" = (current_date - 1))
        select ins.peer as peer
        from ins
            join outs ON ins.peer = outs.peer
        where  (outs.time + (select make_interval(mins => N))) > ins.time;
    end;
    $$ language plpgsql;

-- begin;
-- call pcd_time_out_of_campus('cursor_name', '90');
-- fetch all in "cursor_name";
-- end;

-- 25) Определить для каждого месяца процент ранних входов
drop function if exists fnc_count_of_visits cascade;
create or replace function fnc_count_of_visits(in ppeer text, in ttime time) returns integer as
    $$
    select count(*)
    from (select peer
          from timetracking
          where peer = ppeer
            and timetracking."Time" < ttime
            and state = '1') jojo
    $$
    language sql;

drop procedure if exists pcd_early_visits_for_months cascade;
create or replace procedure pcd_early_visits_for_months(in ref refcursor) as
    $$
    begin
        open ref for
            with months as (select months::date
                            from generate_series('2022-01-01', '2022-12-01', interval '1 month') as months),
                 visits as (select to_char(months::date, 'Month') as month,
                                   sum(fnc_count_of_visits(p.nickname::text, '24:00:00')) as visits,
                                   sum(fnc_count_of_visits(p.nickname::text, '12:00:00')) as early_visits
                            from months
                                     full join peers p on extract(month from months) = extract(month from p.birthday::date)
                            group by 1)
            select month, case when visits = 0 then 0 else early_visits * 100 / visits end as EarlyEntries
            from visits;
    end;
    $$ language plpgsql;

-- begin;
-- call pcd_early_visits_for_months('cursor_name');
-- fetch all in "cursor_name";
-- end;