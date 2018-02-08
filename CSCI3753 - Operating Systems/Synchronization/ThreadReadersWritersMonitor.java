// This is the a simple monitor-based synchronized R/W implementation
// Synchronized tutorial: https://docs.oracle.com/javase/tutorial/essential/concurrency/syncmeth.html

/*
 *
 * Includes
 *
 */
import java.util.Scanner;



/*
 *
 * Main class
 *
 */
public class ThreadReadersWritersMonitor implements Runnable
{

	// private static attributes
	private static ReaderWriterMonitor readerWriter;

	// private attributes
	private int threadNum;
	private boolean writer;

	// static main entry function
	public static void main(String[] args) 
	{

		// init static vars
		ThreadReadersWritersMonitor.readerWriter = new ReaderWriterMonitor();

		// create threads
		for(int i = 0; i < 3; i++)
		{
			(new Thread(new ThreadReadersWritersMonitor(i, true))).start();
			(new Thread(new ThreadReadersWritersMonitor(i, false))).start();
		}

		// wait for user input
		System.out.println("Press any key to exit...");
		Scanner s = new Scanner(System.in);
		String a = s.next();
	}

	// sleep a tick
	public static void sleepATick()
	{
		try
		{
			Thread.sleep(1);
		}
		catch (Exception e)
		{
			// do nothing
		}
	}

	// constructor
	public ThreadReadersWritersMonitor(int threadNum, boolean writer)
	{
		this.threadNum = threadNum;
		this.writer = writer;
	}

	// implemented for Runnable
	public void run()
	{
		while(true)
		{
			if (this.writer == true)
			{
				ThreadReadersWritersMonitor.readerWriter.write("|abcdefghijklmnopqrstuvwxyz-[" + Integer.toString(this.threadNum) + "]", this.threadNum);
			}
			else
			{
				char[] readBuffer = ThreadReadersWritersMonitor.readerWriter.read(this.threadNum);
			}

			// sleep a tick
			ThreadReadersWritersMonitor.sleepATick();
		}
	}
}

// private inner class for reader / writer implemented as a monitor
class ReaderWriterMonitor
{

	// constants
	private final int FILE_SIZE = 100;

	// private attributes
	private char[] buffer = new char[FILE_SIZE];
	private int pointer = 0;

	// write to buffer
	public synchronized void write(String s, int threadNum)
	{
		System.out.println("\r\n\r\n-------------------------------\r\nSTART WRITING: " + Integer.toString(threadNum) + "\r\n-------------------------------\r\n");
		System.out.println("Before write:\r\n" + new String(this.buffer) + "\r\n");
		for(int i = 0; i < s.length(); i++)
		{

			// write a character
			this.pointer = (this.pointer >= FILE_SIZE) ? 0 : this.pointer;
			this.buffer[this.pointer] = s.charAt(i);
			if ((this.pointer + 1) < FILE_SIZE)
			{
				this.buffer[this.pointer + 1] = '@';
			}
			else
			{
				this.buffer[0] = '@';
			}
			this.pointer++;

			// sleep a tick
			ThreadReadersWritersMonitor.sleepATick();
		}
		System.out.println("After write:\r\n" + new String(this.buffer) + "\r\n");
		System.out.println("-------------------------------\r\nSTOP WRITING: " + Integer.toString(threadNum) + "\r\n-------------------------------");
	}

	// read from buffer
	public synchronized char[] read(int threadNum)
	{

		// var init
		char[] retBuffer = new char[FILE_SIZE];

		System.out.println("\r\n\r\n-------------------------------\r\nSTART READING: " + Integer.toString(threadNum) + "\r\n-------------------------------\r\n");
		System.out.println("File buffer:\r\n" + new String(this.buffer) + "\r\n");
		for(int i = 0; i < FILE_SIZE; i++)
		{

			// read a character
			retBuffer[i] = this.buffer[i];

			// sleep a tick
			ThreadReadersWritersMonitor.sleepATick();
		}
		System.out.println("Return buffer:\r\n" + new String(retBuffer) + "\r\n");
		System.out.println("-------------------------------\r\nSTOP READING: " + Integer.toString(threadNum) + "\r\n-------------------------------");
		
		return retBuffer;
	}
}