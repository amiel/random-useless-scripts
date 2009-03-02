-- program1
-- by Amiel Martin
-- October 1st, 2008
--
-- Programm 1 for CS322 with prof Meehan
-- implements the readers writers solution for monitors as described in the CPS example below
-- modeled after http://django.cs.wwu.edu/~meehan/programexample/CPS/RwCps.htm
-- second revision



with ADA.Text_IO;
with ADA.Integer_Text_IO;

with Ada.Numerics.Float_Random;

procedure ReadersWriters is

	task type Reader (number : Integer);
	task type Writer (number : Integer);
	
	-- protected object for getting random floats
	-- we use this for random delays so that each task doesn't always take the same amount of time
	protected Rand is
		procedure reset_seed;
		function get_random return Float;
	private
		seed : Ada.Numerics.Float_Random.Generator;		
	end Rand;
	
	protected Variable is
		-- function read return Integer;
		-- procedure write (data : in Integer);
		entry start_read;
		entry start_write;
		procedure end_read;
		procedure end_write;
	private
		-- these are used to signal the entries
		-- originally, I checked start_read'count and start_write'count
		-- but that ended in deadlock
		oktoread : boolean := false;
		oktowrite : boolean := true;
	
		writing : boolean := false;
		readers : Integer := 0;
		
	end Variable;
	
		-- this is the dumb data that we are trying to protect with all this madness
		shared_data : Integer := 0;
	

	protected body Rand is
		procedure reset_seed is
		begin
			Ada.Numerics.Float_Random.Reset(seed);
		end reset_seed;
	
		function get_random return Float is
		begin
			return Ada.Numerics.Float_Random.Random(seed);
		end get_random;
	end Rand;
	

	protected body Variable is
	
		-- blocks when the writer is writing or oktoread is false
		entry start_read
			when not writing and oktoread is
		begin
			oktowrite := false;
			readers := readers + 1;
			ADA.Text_IO.put_line("start_read : readers(" & Integer'Image(readers) & ")");
		end start_read;
		
		procedure end_read is
		begin
			readers := readers - 1;
			ADA.Text_IO.put_line("end_read : readers(" & Integer'Image(readers) & ")");
			
			-- if a writer is waiting, then do not let any readers start
			if start_write'count > 0 then
				oktoread := false;
			end if;
				
			-- if all readers are finished, then we can trigger the writer
			if readers = 0 then
				oktowrite := true;
			end if;
		end end_read;
	
		-- blocks if there are any readers reading or writers writing
		-- or oktowrite is false
		entry start_write
			when not writing and oktowrite and readers = 0 is
		begin
			oktoread := false;
			oktowrite := false;
			writing := true;
			ADA.Text_IO.put_line("start_write");
		end start_write;
		
		-- if there are readers waiting, then let them proceed
		-- otherwise, trigger the next wirter
		procedure end_write is
		begin
			writing := false;
			if start_read'count > 0 then
				oktoread := true;
			else
				oktowrite := true;
			end if;
			ADA.Text_IO.put_line("end_write");
		end end_write;
		
	
		-- function read return Integer is
		-- begin
		-- 	return shared_data;
		-- end read;
		
		-- procedure write (data : in Integer) is
		-- begin
		-- 	shared_data := shared_data + data;
		-- end write;
	end Variable;

	task body Reader is
		tmp : Integer;
	begin
		loop			
			delay(Duration(Rand.get_random / 10.0));
			Variable.start_read;
			
			-- read global instead
			tmp := shared_data;
			delay(Duration(Rand.get_random / 10.0));
			ADA.Text_IO.put("Reader #" & Integer'Image(number));
			ADA.Text_IO.put_line(" ---------- data(" & Integer'Image(tmp) & ")");
			Variable.end_read;
		end loop;
	end Reader;

	task body Writer is
	begin
		loop
			-- either delay for a really short time or a long time
			if( Integer(Rand.get_random * 2.0) = 0) then
				delay(Duration(Rand.get_random) / 1000.0);
			else
				delay(Duration(Rand.get_random) * 2);				
			end if;
			
			Variable.start_write;			
			ADA.Text_IO.put_line("Writer #" & Integer'Image(number));
			-- manipulate global
			shared_data := shared_data + 1;
			delay(Duration(Rand.get_random) / 100.0);
			Variable.end_write;
		end loop;
	end Writer;


	R1 : Reader (number => 1);
	R2 : Reader (number => 2);
	R3 : Reader (number => 3);
	R4 : Reader (number => 4);
	
	W1 : Writer (number => 1);
	W2 : Writer (number => 2);
begin
	Rand.reset_seed;
end ReadersWriters;