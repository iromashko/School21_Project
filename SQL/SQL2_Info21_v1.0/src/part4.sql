-- 1) Создать хранимую процедуру, которая, не уничтожая базу данных, уничтожает все те таблицы текущей базы данных,
-- имена которых начинаются с фразы 'TableName'.
create table table_x_first (
    id bigint primary key
);

create table table_x_second (
    name varchar
);

create table table_x_third (
    ctime timestamp
);

drop procedure if exists pcd_remove_table cascade;

create or replace procedure pcd_remove_table(in tab_name text) as
    $$
    begin
        for tab_name in ( select table_name
                            from information_schema.tables
                            where table_name like concat(tab_name, '_%'))
            loop
                execute concat('drop table ', tab_name);
            end loop;
    end;
    $$ language plpgsql;

-- call pcd_remove_table('table_x');

-- 2) Создать хранимую процедуру с выходным параметром, которая выводит список имен и параметров всех скалярных
-- SQL функций пользователя в текущей базе данных. Имена функций без параметров не выводить.
-- Имена и список параметров должны выводиться в одну строку. Выходной параметр возвращает количество найденных функций.

drop procedure if exists pcd_count_fnc cascade;

create or replace procedure pcd_count_fnc(out count_tables int) as
    $$
    begin
        with get_params as (select r.routine_name as function,
                                   concat('(', p.parameter_mode, ' ', p.parameter_name, ' ', p.data_type, ')') as params
                            from information_schema.routines as r
                                     join information_schema.parameters as p on r.specific_name = p.specific_name
                            where r.routine_type = 'FUNCTION' and r.specific_schema = 'public' and
                                    p.specific_schema = 'public' and parameter_name is not null),
             f_concat as (select concat(function, ' ', string_agg(params, ','))
                          from get_params
                          group by function)
        select count(*) into count_tables
        from f_concat;
    end;
    $$ language plpgsql;

call pcd_count_fnc(null);

-- 3) Создать хранимую процедуру с выходным параметром, которая уничтожает все SQL DML триггеры в текущей базе данных.
-- Выходной параметр возвращает количество уничтоженных триггеров.

drop procedure if exists pcd_delete_dml_triggers cascade ;

create or replace procedure pcd_delete_dml_triggers(out count_drops int) as
    $$
    declare trg_name text;
            table_name text;
    begin
        select count(distinct trigger_name) into count_drops
        from information_schema.triggers
        where trigger_schema = 'public';
        for trg_name, table_name in (select distinct trigger_name, event_object_table
                                     from information_schema.triggers
                                     where trigger_schema = 'public')
            loop
                execute concat('DROP TRIGGER ', trg_name, ' ON ', table_name);
            end loop;
    end ;
    $$ language plpgsql;

-- call pcd_delete_dml_triggers(null);

-- 4) Создать хранимую процедуру с входным параметром, которая выводит имена и описания типа объектов
-- (только хранимых процедур и скалярных функций), в тексте которых на языке SQL встречается строка, задаваемая параметром процедуры.
drop procedure if exists pcd_finding_names_and_types cascade;

create or replace procedure pcd_finding_names_and_types(in ref refcursor, in pattern text) as
    $$
    begin
        open ref for
            select routine_name as name, routine_type as type
            from information_schema.routines
            where specific_schema = 'public'
              and routine_definition like concat('%', pattern, '%');
    end;
    $$ language plpgsql;

begin;
call pcd_finding_names_and_types('cursor_name', 'trigger');
fetch all in "cursor_name";
end;
