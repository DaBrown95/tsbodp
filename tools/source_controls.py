"""Changed-source controls must make a concrete, reproducible source mutation."""


def mutate(source, control):
    before, after = control['before'], control['after']
    if not before or before == after or before not in source:
        raise ValueError('Changed-source control no longer applies')
    return source.replace(before, after)
