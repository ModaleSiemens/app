tests = [
    [
        'Test-1',
        'test1.cpp'
    ]
]

foreach test : tests
    executable(
        test[0],
        test[1],
        dependencies: lib_app_dep
    )
endforeach