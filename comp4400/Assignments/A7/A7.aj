/*
 * Student Name: Dennis Dao
 * Student Number: 110010116
 * Date: Nov 29, 2023
 */

import java.util.*;

public aspect A7 {
	Set<String> liveVariables = new HashSet<String>(Arrays.asList("z")); // start with z as the only live variable
	ArrayList<Expr> expressions = new ArrayList<Expr>(), liveStatements = new ArrayList<Expr>();;
	ArrayList<String> assignmentVars = new ArrayList<String>(), liveDefinition = new ArrayList<String>();

	// Skip println statements
	void around() : call(* *..print*(..)) && !within(A7) {}

	after() returning(java_cup.runtime.Symbol val) : call(* *..parse()){
		Vector<Statement> statements = ((Program)(val.value)).getStatements();

		for(Statement s : statements){
			Set<String> after = new HashSet<String>(liveVariables);
			Assignment a = (Assignment)s;

			liveVariables.remove(a.getLHS());
			liveVariables.addAll(a.getRHS().getVariables());

			if(after.contains(a.getLHS())){
				liveStatements.add(a.getRHS());
				liveDefinition.add(a.getLHS());
			}
		}

		Collections.reverse(liveStatements);
		Collections.reverse(liveDefinition);
	}

	after() : execution(public static * main(..)){
		for(int i = 0; i < liveStatements.size(); i++){
			System.out.println(liveDefinition.get(i) + " = " + liveStatements.get(i).print());
		}
	}

    public String Expr.print(){
		if(this.isPrimitive() && this.getValue() != null){
			return this.getValue().toString();
		}
		else if(this.isPrimitive() && this.getID() != null){
			return this.getID();
		}
		return "(" + this.getLeft().print() + this.getOp() + this.getRight().print() + ")";
	}

	// Utility to get the variables of an expression
	public Set<String> Expr.getVariables(){
		Set<String> variables = new HashSet<String>();
		if(this.isPrimitive() && this.getValue() != null){
			return variables;
		}
		else if(this.isPrimitive() && this.getID() != null){
			variables.add(this.getID());
			return variables;
		}
		variables.addAll(this.getLeft().getVariables());
		variables.addAll(this.getRight().getVariables());
		return variables;
	}
}