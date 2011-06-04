namespace TestingVector2f
{
  struct Vector2fFixture
  {
    Vector2fFixture()
    {
      a[0] = 1; a[1] = 2;
      b[0] = 5; b[1] = 6;
    }

    tloc::Vec2f a, b, c, d, e;
  };

#define REQUIRE_VEC2F(vec,x,y) REQUIRE((vec[0]) == (Approxf(x)) ); \
  REQUIRE((vec[1]) == (Approxf(y)) );

  TEST_CASE_METHOD(Vector2fFixture, "Math/Vector2f/General", 
    "Vector tests without math operations")
  {
    REQUIRE_VEC2F(a, 1, 2);
    REQUIRE_VEC2F(b, 5, 6);

    c = a;
    REQUIRE_VEC2F(c, 1, 2);
    REQUIRE_VEC2F(a, 1, 2);

    c.Zero();
    REQUIRE_VEC2F(c, 0, 0);

    d = a; e = b; d.Swap(e);
    REQUIRE_VEC2F(d, 5.0f, 6.0f);
    REQUIRE_VEC2F(e, 1.0f, 2.0f);
    REQUIRE_VEC2F(a, 1.0f, 2.0f);
    REQUIRE_VEC2F(b, 5.0f, 6.0f);
  }

  TEST_CASE_METHOD(Vector2fFixture, "Math/Vector2f/[]Operator", 
    "Tests the square bracket operator value retrieval and assignment")
  {
    REQUIRE_VEC2F(a, 1, 2);
    REQUIRE_VEC2F(b, 5, 6);
    a[0] = 10; a[1] = 11;
    b[0] = 20; b[1] = 21;
    REQUIRE_VEC2F(a, 10, 11);
    REQUIRE_VEC2F(b, 20, 21);
  }

  TEST_CASE_METHOD(Vector2fFixture, "Math/Vector2f/SetAndZero", 
                                    "Tests the Set() and Zero() functions")
  {
    a.Set(1);
    REQUIRE_VEC2F(a, 1, 1);
    a.Set(-1);
    REQUIRE_VEC2F(a, -1, -1);

#define BIG_FLOAT -0.987654321f
    a.Set(BIG_FLOAT);
    REQUIRE_VEC2F(a, BIG_FLOAT, BIG_FLOAT);
#undef BIG_FLOAT

    a.Zero();
    REQUIRE_VEC2F(a, 0, 0);
  }

  TEST_CASE_METHOD(Vector2fFixture, "Math/Vector2f/BasicOperations", 
                "Test addition, subtraction, multiplication and division")
  {
    //////////////////////////////////////////////////////////////////////////
    // Addition and subtraction

    // Addition single
    c.Add(a, b);
    REQUIRE_VEC2F(c, 6, 8);

    // Subtraction double
    c.Sub(a, b);
    REQUIRE_VEC2F(c, -4, -4);

    // Addition single
    c.Add(b);
    REQUIRE_VEC2F(c, 1, 2);

    // Subtraction single
    c.Sub(a);
    REQUIRE_VEC2F(c, 0, 0);
    c.Sub(a);
    REQUIRE_VEC2F(c, -1, -2);

    //////////////////////////////////////////////////////////////////////////
    // Multiplication single

    c.Zero();
    c.Mul(a);
    REQUIRE_VEC2F(c, 0, 0);
    c = b; c.Mul(b);
    REQUIRE_VEC2F(c, 25, 36);

    
  }
}