/// Tool Modules
import { Inversify } from '~/tools/vendors';

/// Package Modules
import { Context } from '../context';

/** Explicit Release Module. */
export type Module = Inversify.ContainerModule;
export function Module() {
    return new Inversify.ContainerModule((_) => {
        //  CONTEXT BINDINGS  //

        _.bind(Context).toSelf().inSingletonScope();
    });
}

export namespace Module {
    //  PUBLIC METHODS  //

    /**
     * Handles preloading containers.
     * @param options               Contextual options.
     */
    export async function preload(options: Context.Options = {}) {
        const container = new Inversify.Container(); // build
        container.bind(Context.Options).toConstantValue(options);
        return (await container.load(Module()), container);
    }
}
