package pizzas;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

class TestPizzas {

	private BasePizzas base=new BasePizzas();
	
	@BeforeEach
	public void init() {
		base.addPizzaToMenu(base.createSurpriseWhitePizza());
	}
	
	@Test
	void testAjoutPizza() {
		Pizza p=new Pizza("fromages", 10);
		p.ajoutIngredient(new Ingredient("Mozzarelle", true));
		p.ajoutIngredient(new Ingredient("Talegio", true));
		
		base.addPizzaToMenu(p);
		
		assertEquals(p, base.getPizzaFromMenu("fromages"));
	}
	
	@Test
	void testPizzaEquals() {
		Pizza p = new Pizza("fromages", 10);
		Pizza p2 = new Pizza("fromages", 10);
		assertEquals(p, p2);
	}
	
	@Test
	void testPizzaNotEquals() {
		Pizza p = new Pizza("fromages", 10);
		Pizza p2 = new Pizza("fromages", 20);
		assertNotEquals(p, p2);
	}
	
	@Test
	 void testAjoutIng1() {
		Pizza p=base.getPizzaFromMenu("Surprise blanche");
		System.out.println(p.formattedIngredients());
		var oldSize=p.ingredients().length;
		p.ajoutIngredient(new Ingredient("brocolis", true));
		assertEquals(oldSize+1, p.ingredients().length);
	}

}
