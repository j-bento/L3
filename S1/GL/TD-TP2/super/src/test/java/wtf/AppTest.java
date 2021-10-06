package wtf;

import static org.junit.Assert.assertTrue;

import org.junit.Test;
import org.apache.commons.collections4.MultiValuedMap;
import org.apache.commons.collections4.ArrayListValuedHashMap;

/**
 * Unit test for simple App.
 */
public class AppTest 
{
    MultiValuedMap<String, String> map = new ArrayListValuedHashMap<>();
    //map.put("fruits", "apple");
    
    @Test
    public void shouldAnswerWithTrue()
    {
        assertTrue( true );
    }
}
