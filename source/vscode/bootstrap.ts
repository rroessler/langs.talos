/// Talos Modules
import { Module } from '@/talos/module';
import { Extension } from '@/talos/extension';
import { Container, Inversify } from '@/talos/utilities';

//  PUBLIC METHODS  //

/**
 * Handles activating the extension.
 * @param context               Extension context.
 */
export async function activate(context: Extension.Context) {
    // prepare the current container instance
    const container = new Inversify.Container();

    // bind the container and extension context now
    container.bind(Container).toConstantValue(container);
    container.bind(Extension.Context).toConstantValue(context);

    // load the module to be used now
    await container.load(Module);

    // attempt activation now through the lifecycle service
    await container.get(Extension.Lifecycle).activate();
}
