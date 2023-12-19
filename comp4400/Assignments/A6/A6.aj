/*
 * Student Name: Dennis Dao
 * Student Number: 110010116
 * Date: Nov 18, 2023
 */

public aspect A6 {
    // you need to add variable declarations here for  for counting etc
	public static int Expr.exprCount = 0; 
	int assignmentNo = 0, indent = 0;
	
    //You need to add a few advices for print and evluate

	// Skip println statements
	void around() : call(*   *..print*(..)) && !within(A6) {
		// Don't print anything!
	}

	//count expr
	after(Expr e): execution( Expr.new(..)) && this(e) {
		Expr.exprCount++;
	}

	// Print assignment statement before constructing it
	before(String var, Expr exp): call( Assignment.new(String, Expr))&& args(var, exp) {
		// add your code to print the right trace
		System.out.println("Assignment " + assignmentNo++ + " is: " + var + "=" + exp.print());
		exp.evaluate();
		System.out.println();
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

	public Integer Expr.evaluate(){
		Integer val;

		if(this.isPrimitive() && this.getValue() != null){
			return this.getValue();
		}
		else if(this.isPrimitive() && this.getID() != null){
			return Program.varTable.get(this.getID()).evaluate();
		}
		else{
			Integer leftVal = this.getLeft().evaluate(), rightVal = this.getRight().evaluate();
			String op = this.getOp();

			val = op.equals("+") ? leftVal + rightVal : op.equals("*") ? leftVal * rightVal : 0;
		}
		return val;
	}

	before() : call(* *.evaluate()){
		indent++;
		Expr exp = (Expr)thisJoinPoint.getTarget();

		for(int i = 0, space = indent * 3; i < space; i++){
			System.out.print(" ");
		}
		System.out.println(exp.print() + " ==> ?");
	}

	after() returning(Integer val) : call(* *.evaluate()){
		Expr exp = (Expr)thisJoinPoint.getTarget();
		for(int i = 0, space = indent * 3; i < space; i++){
			System.out.print(" ");
		}
		indent--;
		System.out.println(exp.print() + " ==> " + val);
	}

	after() : execution(public static * main(..)){
		System.out.println("Number of expressions: " + Expr.exprCount);
	}	
}
