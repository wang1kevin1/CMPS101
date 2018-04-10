//-----------------------------------------------------------------------------
//  Kevin Wang
//  kwang43@ucsc.edu
//  PA_1
//
//  Lex.java
//-----------------------------------------------------------------------------

import java.io.*;
import java.util.*;

public class Lex {
	public static void main(String[] args) throws IOException {
		Scanner input = null;
		PrintWriter output = null;
		String[] tokens = null;
		int lineNumber = 0;

		if (args.length != 2) {
			throw new RuntimeException(
					"Usage: Lex   file_in   file_out");
		}

		input = new Scanner(new File(args[0]));

		int lines = 0;
		while (input.hasNextLine()) {
			lines++;
			input.nextLine();
		}

		input.close();

		List list = new List();
		tokens = new String[lines];
		input = new Scanner(new File(args[0]));
		output = new PrintWriter(new FileWriter(args[1]));

		while (input.hasNextLine()) {
			tokens[lineNumber] = input.nextLine();
			lineNumber++;
		}

		list.append(0);

		for (int j = 1; j < tokens.length; ++j) {
			String temp = tokens[j];
			int i = j - 1;

			list.moveBack();

			while (i >= 0 && temp.compareTo(tokens[list.get()]) <= 0) {
				i--;
				list.movePrev();
			}

			if (list.index() >= 0)
				list.append(j);

			else
				list.prepend(j);
		}

		list.moveFront();

		while (list.index() >= 0) {
			output.println(tokens[list.index()]);
			list.moveNext();
		}

		input.close();
		output.close();
	}
}
