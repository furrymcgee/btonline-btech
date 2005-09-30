//----------------------------------------------------------------------------
// UnitSection.java
// ----------------
// Stores information regarding sections of a unit. Holds the contents of
// crits and armor values.
//----------------------------------------------------------------------------

public class UnitSection {
	private int	armor;				// Number of armor points in this section.
	Crit[]		sectionCrits;		// The array of crits in the section.
	Unit		unit;				// Holds reference to the unit.
	
	// Default default constructor. Don't use it!
	UnitSection() {
		// Assume a 12-crit section.
		sectionCrits = new Crit[12];
		unit = null;
	} // end constructor UnitSection
	
	// Default constructor
	UnitSection(Unit inUnit) {
		// Assume a 12-crit section.
		sectionCrits = new Crit[12];
		unit = inUnit;
	} // end constructor UnitSection
	
	// Constructor with argument for variable crit count
	UnitSection(Unit inUnit, int numCrits) {
		// Allow setting of an arbitrary number of crits.
		sectionCrits = new Crit[numCrits];
		unit = inUnit;
	} // end constructor UnitSection
	
/*-----------------------------------------------------------*
   Low-level Methods - Direct Variable Get/Set
 *-----------------------------------------------------------*/
	
	// Returns the amount of armor in this section.
	public int getArmor() {
		return armor;
	} // end getArmor
	
	// Sets the section's armor level.
	public void setArmor(int newArmorVal) {
		armor = newArmorVal;
	} // end getArmor

/*-----------------------------------------------------------*
	Mid-Level Methods
 *-----------------------------------------------------------*/
	
	// Adds a crit to the section's crit array. Currently just
	// over-writes existing crits if you specify an occupied.
	public void addCrit(Crit newCrit, int location) {
		sectionCrits[location] = newCrit;
	} // end addCrit
	
	// Returns a string representation of the section.
	public String toString() {
		String output;		// Output to return.
		
		output = "------------------------------\n" +
				 " Section Overview | Armor: " + armor + "\n" +
				 "------------------------------";
				 
		// Go through the section and show the crits.
		for (int x = 0; x < sectionCrits.length; x++) {
			output += "\n" + x + " " + sectionCrits[x];
		} // end for
				 
		output += "\n------------------------------";
		
		return output;
	} // end toString
	
/*-----------------------------------------------------------*
   Main Method - For Testing Only
 *-----------------------------------------------------------*/
	
	public static void main(String[] args) {
		UnitSection testSection = new UnitSection();
		Crit crit1 = new Crit("Some Multi-Crit");
		Crit crit2 = new Crit("Some Single-Crit");
		testSection.addCrit(crit1,5);
		testSection.addCrit(crit1,6);
		testSection.addCrit(crit2,8);
		System.out.println(testSection.toString());
	} // end main
} // end class UnitSection
