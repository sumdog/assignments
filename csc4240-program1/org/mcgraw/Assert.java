// Routines used for testing assertions.  Used in structure package.
// (c) 1998 McGraw-Hill

package org.mcgraw;

public class Assert
{
    private Assert()
    // pre: An Assert cannot be constructed.
    {
        Assert.fail("Attempt to construct an Assert!?");
    }

    static public void pre(boolean test, String message)
    // pre: result of precondition test.
    // post: does nothing if test true, otherwise abort w/message
    {
        if (test == false) throw new FailedPrecondition(message);
    }

    static public void post(boolean test, String message)
    // pre: result of postcondition test.
    // post: does nothing if test true, otherwise abort w/message
    {
        if (test == false) {
            throw new FailedPostcondition(message);
        }
    }

    static public void condition(boolean test, String message)
    // pre: result of general condition test.
    // post: does nothing if test true, otherwise abort w/message
    {
        if (test == false) throw new FailedAssertion(message);
    }

    static public void fail(String message)
    // post: throws error with message
    {
        throw new FailedAssertion(message);
    }
}

class FailedAssertion extends Error
{
    public FailedAssertion(String reason)
    // post: constructs a new failed assertion error
    {
        super("\nAssertion that failed: " + reason);
    }
}

class FailedPrecondition extends FailedAssertion
{
    public FailedPrecondition(String reason)
    // post: constructs a new failed precondition
    {
        super("\nA precondition: " + reason);
    }
}

class FailedPostcondition extends FailedAssertion
{
    public FailedPostcondition(String reason)
    // post: constructs a new failed postcondition
    {
        super("\nA postcondition: " + reason);
    }
}

