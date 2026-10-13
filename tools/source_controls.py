"""Changed-source controls must make a concrete, reproducible source mutation."""


def validate_control(control):
    if (not isinstance(control, dict)
            or not isinstance(control.get('before'), str)
            or not isinstance(control.get('after'), str)
            or not control['before'] or control['before'] == control['after']):
        raise ValueError('Changed-source control must specify different source strings')


def require_negative_controls(functions):
    for function in functions:
        try:
            validate_control(function.get('negative_control'))
            if function.get('inline_glue'):
                validate_control(function['inline_glue'].get('negative_control'))
        except ValueError as error:
            raise ValueError(f"Required control for {function['name']}: {error}") from error


def verified_comparison(result, *, controls_compiled=False):
    def rejected(control):
        return (isinstance(control, dict) and control.get('identical') is False
                and control.get('rejected') is True)

    return (controls_compiled is True and result.get('identical') is True
            and rejected(result.get('negative_control'))
            and (not result.get('inline_glue')
                 or rejected(result.get('inline_glue_control'))))


def mutate(source, control):
    validate_control(control)
    before, after = control['before'], control['after']
    if before not in source:
        raise ValueError('Changed-source control no longer applies')
    return source.replace(before, after)
